set nu
set ts=4
set expandtab
set listchars=eol:$,tab:>-,trail:~,extends:>,precedes:<
set list

if has("cscope")
    if filereadable("cscope.out")
        cs add cscope.out
    endif
endif
