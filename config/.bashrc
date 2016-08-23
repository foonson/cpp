alias fii='for i in '
export PS1=" [$(tty|cut -d/ -f3,4)] \u \h \w \n\#$ "
