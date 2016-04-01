set nu
set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab
"set ts=4
"set smartindent
"set shiftwidth=4
"set expandtab	"tab to spaces
set listchars=eol:$,tab:>-,trail:~,extends:>,precedes:<
"set list		"show tabs and spaces

highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%81v.\+/

"filetype plugin indent on
"syn on se title

if has("cscope")
    if filereadable("cscope.out")
        cs add cscope.out
    endif
endif
