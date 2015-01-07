set nu
set ts=4
"set smartindent
set shiftwidth=4
set expandtab
set listchars=eol:$,tab:>-,trail:~,extends:>,precedes:<

highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%81v.\+/

"set list
"filetype plugin indent on
"syn on se title

if has("cscope")
    if filereadable("cscope.out")
        cs add cscope.out
    endif
endif
