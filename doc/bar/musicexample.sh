case $1 in
  1) mpc toggle; exit;;# right click
  2) mpc next; exit;;  # left click
  3) mpc pause; exit;; # middle click
esac

[[ "$(mpc current)" == "" ]] && { printf "\xf1 no music "; exit;}

[[ $(mpc status) == *'[playing]'* ]] || printf "\xf2" # the \xf2 makes the bar use the secondary color for this module
[[ $(mpc status) == *'[playing]'* ]] && printf "\xf1" # the \xf1 makes the bar use the primary color for this module
if [[ $1 == icon ]]; then
  [[ $(mpc status) == *'[playing]'* ]] || printf "  \n"
  [[ $(mpc status) == *'[playing]'* ]] && printf "  \n"
  exit
fi

mpc status \
  |sed "/^volume:/d" \
  | tac \
  | sed -e "s/\\[paused\\].*/  /g;s/\\[playing\\].*/  /g" \
  | tr -d '\n' | sed "s/\;//g" \
  | awk -v len=40 '{ if (length($0) > len) print substr($0, 1, len-3) "..."; else print; }'
