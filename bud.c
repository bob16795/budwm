void
bud(Monitor *mon) {
  unsigned int n, nx, ny, nw, nh;
  unsigned int A = 0, B = 0, C = 0, D = 0;
  Client *c;

  for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++) {
    if (c->container == 1){
      A = 1;
    } else if (c->container == 2){
      B = 1;
    } else if (c->container == 3){
      C = 1;
    } else if (c->container == 4){
      D = 1;
    }
  }
  if(n == 0)
    return;


  for(c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
    nx = mon->wx + gappso;
    ny = mon->wy + 18 + gappso;
    nw = mon->ww - gappso;
    nh = mon->wh - 18 - gappso;
    if (c->container == 1){
      if (C) nh = 171 - gappsi;
      if (B || D) nw = nw - 450 - gappsi;
      nw = nw - gappso;
    } else if (c->container == 2){
      if (A || C) nx = nw - 450 + gappsi;
      if (A || C) nw = 450 - gappsi;
      if (D) nh = 300 - gappsi;
    } else if (c->container == 3){
      if (B || D) nw = nw - 450 - gappsi;
      nw = nw - gappso;
      if (A) nh = nh - 171 - gappsi;
      nh = nh - gappso;
      if (A) ny = ny + 171 + gappsi;
    } else if (c->container == 4){
      if (A || C) nx = nw - 450 + gappsi;
      if (A || C) nw = 450 - gappsi;
      if (B) nh = nh - 300 - gappsi;
      nh = nh - gappso;
      if (B) ny = ny + 300 + gappsi;
    }
    resize(c, nx, ny, nw-2 * c->bw, nh-2 * c->bw, False);
  }
}

