if &cp | set nocp | endif
nmap  : wincmd h
let s:cpo_save=&cpo
set cpo&vim
nmap <NL> : wincmd j
nmap  : wincmd k
nmap  : wincmd l
map  :w:! chmod +x %; ./%
map Q gq
nmap gx <Plug>NetrwBrowseX
nmap <F7> : wa!  : silent! make  :cw  :redraw!
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nnoremap <silent> <F11> :call conque_term#exec_file()
nmap <F9> :ConqueTerm bash 
nmap <F3> : w!  :make % 
nmap <F2> :w! 
inoremap  u
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set backup
set backupdir=~/templates/vim
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set history=50
set hlsearch
set incsearch
set mouse=a
set ruler
set shiftwidth=2
set showcmd
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=2
" vim: set ft=vim :
