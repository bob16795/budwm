void
bud(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  Client *c;

  int basplit = (mon->ww - absplit);
  
  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    c->isframe = 1;
    if (c->container == 1){
      A = 1;
    } else if (c->container == 2){
      B = 1;
    } else if (c->container == 3){
      C = 1;
    } else if (c->container == 4){
      D = 1;
    }
    if (c->isfloating)
      c->isframe = 1;
    if (c->isfullscreen)
      c->isframe = 0;
  }
  if(n == 0)
    return;

  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx + gappso;
    ny = mon->wy + gappso;
    nw = mon->ww - gappso;
    nh = mon->wh - gappso;
    if (c->container == 1){
      if (C) nh = acsplit - gappsi;
      if (B || D) nw = nw - basplit - gappsi;
      nw = nw - gappso;
      if (!C) nh = nh - gappso;
    } else if (c->container == 2){
      if (A || C) nx = nx + absplit - gappso;
      if (A || C) nw = basplit - gappsi;
      else nw = nw - gappso;
      if (D) nh = bdsplit - gappsi;
      if (!D) nh = nh - gappso;
    } else if (c->container == 3){
      if (B || D) nw = nw - basplit - gappsi;
      nw = nw - gappso;
      if (A) nh = nh - acsplit - gappsi;
      nh = nh - gappso;
      if (A) ny = ny + acsplit + gappsi;
    } else if (c->container == 4){
      if (A || C) nx = nx+ absplit - gappso;
      if (A || C) nw = basplit - gappsi;
      else nw = nw - gappso;
      if (B) nh = nh - bdsplit - gappsi;
      nh = nh - gappso;
      if (B) ny = ny + bdsplit + gappsi;

    }
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}

void
budnogaps(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  Client *c;

  int basplit = (mon->ww - absplit);
  
  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    if (c->container == 1){
      A = 1;
      c->isframe = 0;
    } else if (c->container == 2){
      B = 1;
      c->isframe = 0;
    } else if (c->container == 3){
      C = 1;
      c->isframe = 1;
    } else if (c->container == 4){
      D = 1;
      c->isframe = 1;
    }
    if (c->isfullscreen)
      c->isframe = 0;
  }
  if(n == 0)
    return;

  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx;
    ny = mon->wy;
    nw = mon->ww;
    nh = mon->wh;
    if (c->container == 1){
      if (C) nh = acsplit;
      if (B || D) nw = nw - basplit;
    } else if (c->container == 2){
      if (A || C) nx = nx + absplit;
      if (A || C) nw = basplit;
      if (D) nh = bdsplit;
      if (!D) nh = nh;
    } else if (c->container == 3){
      if (B || D) nw = nw - basplit;
      if (A) nh = nh - acsplit;
      if (A) ny = ny + acsplit;
      if (!A) c->isframe = 0;
    } else if (c->container == 4){
      if (A || C) nx = nx + absplit;
      if (A || C) nw = basplit;
      if (B) nh = nh - bdsplit;
      nh = nh;
      if (B) ny = ny + bdsplit;
      if (!B) c->isframe = 0;
    }
    if (!mon->showbar)
      c->isframe = 1;
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}

