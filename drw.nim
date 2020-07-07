##  See LICENSE file for copyright and license details.

import
  drw, util

const
  UTF_INVALID* = 0x0000FFFD
  UTF_SIZ* = 4

var utfbyte*: array[UTF_SIZ + 1, cuchar] = [0x00000080, 0, 0x000000C0, 0x000000E0,
                                     0x000000F0]

var utfmask*: array[UTF_SIZ + 1, cuchar] = [0x000000C0, 0x00000080, 0x000000E0,
                                     0x000000F0, 0x000000F8]

var utfmin*: array[UTF_SIZ + 1, clong] = [0, 0, 0x00000080, 0x00000800, 0x00010000]

var utfmax*: array[UTF_SIZ + 1, clong] = [0x0010FFFF, 0x0000007F, 0x000007FF, 0x0000FFFF,
                                   0x0010FFFF]

proc utf8decodebyte*(c: char; i: ptr csize): clong =
  i[] = 0
  while i[] < (UTF_SIZ + 1):
    if (cast[cuchar](c) and utfmask[i[]]) == utfbyte[i[]]:
      return cast[cuchar](c) and not utfmask[i[]]
    inc((i[]))
  return 0

proc utf8validate*(u: ptr clong; i: csize): csize =
  if not BETWEEN(u[], utfmin[i], utfmax[i]) or BETWEEN(u[], 0x0000D800, 0x0000DFFF):
    u[] = UTF_INVALID
  i = 1
  while u[] > utfmax[i]:
    nil
    inc(i)
  return i

proc utf8decode*(c: cstring; u: ptr clong; clen: csize): csize =
  var
    i: csize
    j: csize
    len: csize
    `type`: csize
  var udecoded: clong
  u[] = UTF_INVALID
  if not clen:
    return 0
  udecoded = utf8decodebyte(c[0], addr(len))
  if not BETWEEN(len, 1, UTF_SIZ):
    return 1
  i = 1
  j = 1
  while i < clen and j < len:
    udecoded = (udecoded shl 6) or utf8decodebyte(c[i], addr(`type`))
    if `type`:
      return j
    inc(i)
    inc(j)
  if j < len:
    return 0
  u[] = udecoded
  utf8validate(u, len)
  return len

proc drw_create*(dpy: ptr Display; screen: cint; root: Window; w: cuint; h: cuint): ptr Drw =
  var drw: ptr Drw = ecalloc(1, sizeof((Drw)))
  drw.dpy = dpy
  drw.screen = screen
  drw.root = root
  drw.w = w
  drw.h = h
  drw.drawable = XCreatePixmap(dpy, root, w, h, DefaultDepth(dpy, screen))
  drw.gc = XCreateGC(dpy, root, 0, nil)
  XSetLineAttributes(dpy, drw.gc, 1, LineSolid, CapButt, JoinMiter)
  return drw

proc drw_resize*(drw: ptr Drw; w: cuint; h: cuint) =
  if not drw:
    return
  drw.w = w
  drw.h = h
  if drw.drawable:
    XFreePixmap(drw.dpy, drw.drawable)
  drw.drawable = XCreatePixmap(drw.dpy, drw.root, w, h,
                             DefaultDepth(drw.dpy, drw.screen))

proc drw_free*(drw: ptr Drw) =
  XFreePixmap(drw.dpy, drw.drawable)
  XFreeGC(drw.dpy, drw.gc)
  free(drw)

##  This function is an implementation detail. Library users should use
##  drw_fontset_create instead.
##

proc xfont_create*(drw: ptr Drw; fontname: cstring; fontpattern: ptr FcPattern): ptr Fnt =
  var font: ptr Fnt
  var xfont: ptr XftFont = nil
  var pattern: ptr FcPattern = nil
  if fontname:
    ##  Using the pattern found at font->xfont->pattern does not yield the
    ##  same substitution results as using the pattern returned by
    ##  FcNameParse; using the latter results in the desired fallback
    ##  behaviour whereas the former just results in missing-character
    ##  rectangles being drawn, at least with some fonts.
    if not (xfont = XftFontOpenName(drw.dpy, drw.screen, fontname)):
      fprintf(stderr, "error, cannot load font from name: \'%s\'\n", fontname)
      return nil
    if not (pattern = FcNameParse(cast[ptr FcChar8](fontname))):
      fprintf(stderr, "error, cannot parse font name to pattern: \'%s\'\n",
              fontname)
      XftFontClose(drw.dpy, xfont)
      return nil
  elif fontpattern:
    if not (xfont = XftFontOpenPattern(drw.dpy, fontpattern)):
      fprintf(stderr, "error, cannot load font from pattern.\n")
      return nil
  else:
    die("no font specified.")
  ##  Do not allow using color fonts. This is a workaround for a BadLength
  ##  error from Xft with color glyphs. Modelled on the Xterm workaround. See
  ##  https://bugzilla.redhat.com/show_bug.cgi?id=1498269
  ##  https://lists.suckless.org/dev/1701/30932.html
  ##  https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=916349
  ##  and lots more all over the internet.
  ##
  var iscol: FcBool
  if FcPatternGetBool(xfont.pattern, FC_COLOR, 0, addr(iscol)) == FcResultMatch and
      iscol:
    XftFontClose(drw.dpy, xfont)
    return nil
  font = ecalloc(1, sizeof((Fnt)))
  font.xfont = xfont
  font.pattern = pattern
  font.h = xfont.ascent + xfont.descent
  font.dpy = drw.dpy
  return font

proc xfont_free*(font: ptr Fnt) =
  if not font:
    return
  if font.pattern:
    FcPatternDestroy(font.pattern)
  XftFontClose(font.dpy, font.xfont)
  free(font)

proc drw_fontset_create*(drw: ptr Drw; fonts: ptr cstring; fontcount: csize): ptr Fnt =
  var
    cur: ptr Fnt
    ret: ptr Fnt = nil
  var i: csize
  if not drw or not fonts:
    return nil
  i = 1
  while i <= fontcount:
    if (cur = xfont_create(drw, fonts[fontcount - i], nil)):
      cur.next = ret
      ret = cur
    inc(i)
  return ret

proc drw_fontset_free*(font: ptr Fnt) =
  if font:
    drw_fontset_free(font.next)
    xfont_free(font)

proc drw_clr_create*(drw: ptr Drw; dest: ptr Clr; clrname: cstring) =
  if not drw or not dest or not clrname:
    return
  if not XftColorAllocName(drw.dpy, DefaultVisual(drw.dpy, drw.screen),
                         DefaultColormap(drw.dpy, drw.screen), clrname, dest):
    die("error, cannot allocate color \'%s\'", clrname)

##  Wrapper to create color schemes. The caller has to call free(3) on the
##  returned color scheme when done using it.

proc drw_scm_create*(drw: ptr Drw; clrnames: ptr cstring; clrcount: csize): ptr Clr =
  var i: csize
  var ret: ptr Clr
  ##  need at least two colors for a scheme
  if not drw or not clrnames or clrcount < 2 or
      not (ret = ecalloc(clrcount, sizeof((XftColor)))):
    return nil
  i = 0
  while i < clrcount:
    drw_clr_create(drw, addr(ret[i]), clrnames[i])
    inc(i)
  return ret

proc drw_setfontset*(drw: ptr Drw; set: ptr Fnt) =
  if drw:
    drw.fonts = set

proc drw_setscheme*(drw: ptr Drw; scm: ptr Clr) =
  if drw:
    drw.scheme = scm

proc drw_rect*(drw: ptr Drw; x: cint; y: cint; w: cuint; h: cuint; filled: cint; invert: cint) =
  if not drw or not drw.scheme:
    return
  if filled != 2:
    XSetForeground(drw.dpy, drw.gc, if invert: drw.scheme[ColBg].pixel else: drw.scheme[
        ColFg].pixel)
    if filled:
      XFillRectangle(drw.dpy, drw.drawable, drw.gc, x, y, w, h)
    else:
      XDrawRectangle(drw.dpy, drw.drawable, drw.gc, x, y, w - 1, h - 1)
  else:
    XSetForeground(drw.dpy, drw.gc, drw.scheme[ColBorder].pixel)
    XFillRectangle(drw.dpy, drw.drawable, drw.gc, x, y, w, h)

proc drw_text*(drw: ptr Drw; x: cint; y: cint; w: cuint; h: cuint; lpad: cuint; text: cstring;
              invert: cint): cint =
  var buf: array[1024, char]
  var ty: cint
  var ew: cuint
  var d: ptr XftDraw = nil
  var
    usedfont: ptr Fnt
    curfont: ptr Fnt
    nextfont: ptr Fnt
  var
    i: csize
    len: csize
  var
    utf8strlen: cint
    utf8charlen: cint
    render: cint = x or y or w or h
  var utf8codepoint: clong = 0
  var utf8str: cstring
  var fccharset: ptr FcCharSet
  var fcpattern: ptr FcPattern
  var match: ptr FcPattern
  var result: XftResult
  var charexists: cint = 0
  if not drw or (render and not drw.scheme) or not text or not drw.fonts:
    return 0
  if not render:
    w = not w
  else:
    XSetForeground(drw.dpy, drw.gc, drw.scheme[if invert: ColFg else: ColBg].pixel)
    XFillRectangle(drw.dpy, drw.drawable, drw.gc, x, y, w, h)
    d = XftDrawCreate(drw.dpy, drw.drawable, DefaultVisual(drw.dpy, drw.screen),
                    DefaultColormap(drw.dpy, drw.screen))
    inc(x, lpad)
    dec(w, lpad)
  usedfont = drw.fonts
  while 1:
    utf8strlen = 0
    utf8str = text
    nextfont = nil
    while text[]:
      utf8charlen = utf8decode(text, addr(utf8codepoint), UTF_SIZ)
      curfont = drw.fonts
      while curfont:
        charexists = charexists or
            XftCharExists(drw.dpy, curfont.xfont, utf8codepoint)
        if charexists:
          if curfont == usedfont:
            inc(utf8strlen, utf8charlen)
            inc(text, utf8charlen)
          else:
            nextfont = curfont
          break
        curfont = curfont.next
      if not charexists or nextfont:
        break
      else:
        charexists = 0
    if utf8strlen:
      drw_font_getexts(usedfont, utf8str, utf8strlen, addr(ew), nil)
      ##  shorten text if necessary
      len = MIN(utf8strlen, sizeof((buf)) - 1)
      while len and ew > w:
        drw_font_getexts(usedfont, utf8str, len, addr(ew), nil)
        dec(len)
      if len:
        memcpy(buf, utf8str, len)
        buf[len] = '\x00'
        if len < utf8strlen:
          i = len
          while i and i > len - 3:
            ##  NOP
            buf[dec(i)] = '.'
        if render:
          ty = y + (h - usedfont.h) div 2 + usedfont.xfont.ascent
          XftDrawStringUtf8(d, addr(drw.scheme[if invert: ColBg else: ColFg]),
                            usedfont.xfont, x, ty, cast[ptr XftChar8](buf), len)
        inc(x, ew)
        dec(w, ew)
    if not text[]:
      break
    elif nextfont:
      charexists = 0
      usedfont = nextfont
    else:
      ##  Regardless of whether or not a fallback font is found, the
      ##  character must be drawn.
      charexists = 1
      fccharset = FcCharSetCreate()
      FcCharSetAddChar(fccharset, utf8codepoint)
      if not drw.fonts.pattern:
        ##  Refer to the comment in xfont_create for more information.
        die("the first font in the cache must be loaded from a font string.")
      fcpattern = FcPatternDuplicate(drw.fonts.pattern)
      FcPatternAddCharSet(fcpattern, FC_CHARSET, fccharset)
      FcPatternAddBool(fcpattern, FC_SCALABLE, FcTrue)
      FcPatternAddBool(fcpattern, FC_COLOR, FcFalse)
      FcConfigSubstitute(nil, fcpattern, FcMatchPattern)
      FcDefaultSubstitute(fcpattern)
      match = XftFontMatch(drw.dpy, drw.screen, fcpattern, addr(result))
      FcCharSetDestroy(fccharset)
      FcPatternDestroy(fcpattern)
      if match:
        usedfont = xfont_create(drw, nil, match)
        if usedfont and XftCharExists(drw.dpy, usedfont.xfont, utf8codepoint):
          curfont = drw.fonts
          while curfont.next:
            ##  NOP
            curfont = curfont.next
          curfont.next = usedfont
        else:
          xfont_free(usedfont)
          usedfont = drw.fonts
  if d:
    XftDrawDestroy(d)
  return x + (if render: w else: 0)

proc drw_map*(drw: ptr Drw; win: Window; x: cint; y: cint; w: cuint; h: cuint) =
  if not drw:
    return
  XCopyArea(drw.dpy, drw.drawable, win, drw.gc, x, y, w, h, x, y)
  XSync(drw.dpy, False)

proc drw_fontset_getwidth*(drw: ptr Drw; text: cstring): cuint =
  if not drw or not drw.fonts or not text:
    return 0
  return drw_text(drw, 0, 0, 0, 0, 0, text, 0)

proc drw_font_getexts*(font: ptr Fnt; text: cstring; len: cuint; w: ptr cuint; h: ptr cuint) =
  var ext: XGlyphInfo
  if not font or not text:
    return
  XftTextExtentsUtf8(font.dpy, font.xfont, cast[ptr XftChar8](text), len, addr(ext))
  if w:
    w[] = ext.xOff
  if h:
    h[] = font.h

proc drw_cur_create*(drw: ptr Drw; shape: cint): ptr Cur =
  var cur: ptr Cur
  if not drw or not (cur = ecalloc(1, sizeof((Cur)))):
    return nil
  cur.cursor = XCreateFontCursor(drw.dpy, shape)
  return cur

proc drw_cur_free*(drw: ptr Drw; cursor: ptr Cur) =
  if not cursor:
    return
  XFreeCursor(drw.dpy, cursor.cursor)
  free(cursor)
