void fixcontainer(unsigned int *posammount, unsigned int *nw, unsigned int *nx, unsigned int *nh, unsigned int *ny, unsigned int ammount, unsigned int mode);
void fixframe(Client *c, unsigned int *nw, unsigned int *nx, unsigned int *nh, unsigned int *ny);
void
fixcontainer(unsigned int *posammount, unsigned int *nw, unsigned int *nx, unsigned int *nh, unsigned int *ny, unsigned int ammount, unsigned int mode) {
  if (*posammount + 1 == ammount) {
    if (mode == 2) {
      int change = *nx + *nw;
      *nx += *posammount * (*nw / ammount);
      *nw = *nw / ammount;
      *nw += (change - (*nx + *nw) );
    } 
    else if (mode == 3) {
      int change = *ny + *nh;
      *ny += *posammount * (*nh / ammount);
      *nh = *nh / ammount;
      *nh += (change - (*ny + *nh) );
    }
  } else {
    if (mode == 2) {
      *nx += *posammount * (*nw / ammount);
      *nw = (*nw / ammount);
    }
    else if (mode == 3) {
      *nh = (*nh / ammount);
      *ny += *posammount * *nh;
    }
  }
  *posammount += 1;
}

void
fixframe(Client *c, unsigned int *nw, unsigned int *nx, unsigned int *nh, unsigned int *ny){

}

void
bud(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  unsigned int Ap = 0, Bp = 0, Cp = 0, Dp = 0;
  Client *c;
  
  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    c->isframe = 1;
    if (c->container == 5)
      c->container = 3;
    if (c->container == 1){
      A += 1;
    } else if (c->container == 2){
      B += 1;
    } else if (c->container == 3){
      C += 1;
    } else if (c->container == 4){
      D += 1;
    }
    if (c->isfloating)
      c->isframe = 1;
    if (c->isfullscreen)
      c->isframe = 0;
  }
  if(n == 0)
    return;

  int acsplitn = acsplit;
  if (acsplitn < 0)
    acsplitn += mon->wh;
  acsplitn -= (bh * mon->showbar);
  int bdsplitn = bdsplit;
  if (bdsplitn < 0)
    bdsplitn += mon->wh;
  bdsplitn -= (bh * mon->showbar);
  int absplitn = absplit;
  if (absplitn < 0)
    absplitn += mon->ww;
  int basplit = (mon->ww - absplitn);
  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx + gappso;
    ny = mon->wy + gappso;
    nw = mon->ww - gappso;
    nh = mon->wh - gappso;
    if (c->container == 1){
      if (C) nh = acsplitn - gappsi;
      if (B || D) nw = nw - basplit - gappsi;
      nw = nw - gappso;
      if (!C) nh = nh - gappso;
      fixcontainer(&Ap, &nw, &nx, &nh, &ny, A, amode);
    } else if (c->container == 2){
      if (A || C) nx = nx + absplitn - gappso;
      if (A || C) nw = basplit - gappso;
      else nw = nw - gappso;
      if (D) nh = bdsplitn - gappsi;
      if (!D) nh = nh - gappso;
      fixcontainer(&Bp, &nw, &nx, &nh, &ny, B, bmode);
    } else if (c->container == 3){
      if (B || D) nw = nw - basplit - gappsi;
      nw = nw - gappso;
      if (A) nh = nh - acsplitn - gappsi;
      nh = nh - gappso;
      if (A) ny = ny + acsplitn + gappsi;
      fixcontainer(&Cp, &nw, &nx, &nh, &ny, C, cmode);
    } else if (c->container == 4){
      if (A || C) nx = nx + absplitn - gappso;
      if (A || C) nw = basplit - gappso;
      else nw = nw - gappso;
      if (B) nh = nh - bdsplitn - gappsi;
      nh = nh - gappso;
      if (B) ny = ny + bdsplitn + gappsi;
      fixcontainer(&Dp, &nw, &nx, &nh, &ny, D, dmode);
    }
    fixframe(c, &nw, &nx, &nh, &ny);
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}

void
budnogaps(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  unsigned int Ap = 0, Bp = 0, Cp = 0, Dp = 0;
  Client *c;

  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    if (c->container == 5)
      c->container = 3;
    if (c->container == 1){
      A += 1;
      c->isframe = 0;
    } else if (c->container == 2){
      B += 1;
      c->isframe = 0;
    } else if (c->container == 3){
      C += 1;
      c->isframe = 1;
    } else if (c->container == 4){
      D += 1;
      c->isframe = 1;
    }
    if (c->isfullscreen)
      c->isframe = 0;
  }
  if(n == 0)
    return;

  int acsplitn = acsplit;
  if (acsplitn < 0)
    acsplitn += mon->wh;
  acsplitn -= (bh * mon->showbar);
  int bdsplitn = bdsplit;
  if (bdsplitn < 0)
    bdsplitn += mon->wh;
  bdsplitn -= (bh * mon->showbar);
  int absplitn = absplit;
  if (absplitn < 0)
    absplitn += mon->ww;
  int basplit = (mon->ww - absplitn);
  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx;
    ny = mon->wy;
    nw = mon->ww;
    nh = mon->wh;
    if (c->container == 1){
      if (C) nh = acsplitn;
      if (B || D) nw = nw - basplit;
      fixcontainer(&Ap, &nw, &nx, &nh, &ny, A, amode);
    } else if (c->container == 2){
      if (A || C) nx = nx + absplitn;
      if (A || C) nw = basplit;
      if (D) nh = bdsplitn;
      if (!D) nh = nh;
      fixcontainer(&Bp, &nw, &nx, &nh, &ny, B, bmode);
    } else if (c->container == 3){
      if (B || D) nw = nw - basplit;
      if (A) nh = nh - acsplitn;
      if (A) ny = ny + acsplitn;
      if (!A) c->isframe = 0;
      fixcontainer(&Cp, &nw, &nx, &nh, &ny, C, cmode);
    } else if (c->container == 4){
      if (A || C) nx = nx + absplitn;
      if (A || C) nw = basplit;
      if (B) nh = nh - bdsplitn;
      nh = nh;
      if (B) ny = ny + bdsplitn;
      if (!B) c->isframe = 0;
      fixcontainer(&Dp, &nw, &nx, &nh, &ny, D, dmode);
    }
    if (!mon->showbar)
      c->isframe = 1;
    fixframe(c, &nw, &nx, &nh, &ny);
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}

void
budnoigaps(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  unsigned int Ap = 0, Bp = 0, Cp = 0, Dp = 0;
  Client *c;

  
  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    c->isframe = 0;
    if (c->container == 5)
      c->container = 3;
    if (c->container == 1){
      A += 1;
    } else if (c->container == 2){
      B += 1;
    } else if (c->container == 3){
      C += 1;
    } else if (c->container == 4){
      D += 1;
    }
    if (c->isfloating)
      c->isframe = 1;
    if (c->isfullscreen)
      c->isframe = 0;
  }
  if(n == 0)
    return;

  int acsplitn = acsplit;
  if (acsplitn < 0)
    acsplitn += mon->wh;
  acsplitn -= (bh * mon->showbar);
  int bdsplitn = bdsplit;
  if (bdsplitn < 0)
    bdsplitn += mon->wh;
  bdsplitn -= (bh * mon->showbar);
  int absplitn = absplit;
  if (absplitn < 0)
    absplitn += mon->ww;
  int basplit = (mon->ww - absplitn);
  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx + gappso;
    ny = mon->wy + gappso;
    nw = mon->ww - gappso;
    nh = mon->wh - gappso;
    if (c->container == 1){
      if (C) nh = acsplitn;
      if (B || D) nw = nw - basplit;
      nw = nw - gappso;
      if (!C) nh = nh - gappso;
      fixcontainer(&Ap, &nw, &nx, &nh, &ny, A, amode);
    } else if (c->container == 2){
      if (A || C) nx = nx + absplitn - 2 * gappso;
      if (A || C) nw = basplit; 
      else nw = nw - gappso;
      if (D) nh = bdsplitn;
      if (!D) nh = nh - gappso;
      fixcontainer(&Bp, &nw, &nx, &nh, &ny, B, bmode);
    } else if (c->container == 3){
      if (B || D) nw = nw - basplit;
      nw = nw - gappso;
      if (A) nh = nh - acsplitn;
      nh = nh - gappso;
      if (A) ny = ny + acsplitn;
      fixcontainer(&Cp, &nw, &nx, &nh, &ny, C, cmode);
    } else if (c->container == 4){
      if (A || C) nx = nx + absplitn - 2 * gappso;
      if (A || C) nw = basplit;
      else nw = nw - gappso;
      if (B) nh = nh - bdsplitn;
      nh = nh - gappso;
      if (B) ny = ny + bdsplitn;
      fixcontainer(&Dp, &nw, &nx, &nh, &ny, D, dmode);
    }
    fixframe(c, &nw, &nx, &nh, &ny);
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}

void
budnoogaps(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  unsigned int Ap = 0, Bp = 0, Cp = 0, Dp = 0;
  Client *c;
  
  
  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    if (c->container == 5)
      c->container = 3;
    if (c->container == 1){
      A += 1;
      c->isframe = 0;
    } else if (c->container == 2){
      B += 1;
      c->isframe = 0;
    } else if (c->container == 3){
      C += 1;
      c->isframe = 1;
    } else if (c->container == 4){
      D += 1;
      c->isframe = 1;
    }
    if (c->isfullscreen)
      c->isframe = 0;
  }

  if(n == 0)
    return;

  int acsplitn = acsplit;
  if (acsplitn < 0)
    acsplitn += mon->wh;
  acsplitn -= (bh * mon->showbar);
  int bdsplitn = bdsplit;
  if (bdsplitn < 0)
    bdsplitn += mon->wh;
  bdsplitn -= (bh * mon->showbar);
  int absplitn = absplit;
  if (absplitn < 0)
    absplitn += mon->ww;
  int basplit = (mon->ww - absplitn);
  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx;
    ny = mon->wy;
    nw = mon->ww;
    nh = mon->wh;
    if (c->container == 1){
      if (C) nh = acsplitn - gappsi;
      if (B || D) nw = nw - basplit - gappsi;
      fixcontainer(&Ap, &nw, &nx, &nh, &ny, A, amode);
    } else if (c->container == 2){
      if (A || C) nx = nx + absplitn;
      if (A || C) nw = basplit;
      if (D) nh = bdsplitn - gappsi;
      fixcontainer(&Bp, &nw, &nx, &nh, &ny, B, bmode);
    } else if (c->container == 3){
      if (B || D) nw = nw - basplit - gappsi;
      if (A) nh = nh - acsplitn - gappsi;
      if (A) ny = ny + acsplitn + gappsi;
      fixcontainer(&Cp, &nw, &nx, &nh, &ny, C, cmode);
    } else if (c->container == 4){
      if (A || C) nx = nx + absplitn;
      if (A || C) nw = basplit;
      if (B) nh = nh - bdsplitn - gappsi;
      if (B) ny = ny + bdsplitn + gappsi;
      fixcontainer(&Dp, &nw, &nx, &nh, &ny, D, dmode);
    }
    fixframe(c, &nw, &nx, &nh, &ny);
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}
