let mapleader=","

"Tabs appear 4 spaces
set tabstop=4
set shiftwidth=4
set expandtab

"Map actual tab to Shift-Tab
inoremap <S-Tab> <C-V><Tab>

"File type detection
filetype indent plugin on

"Better tab-completion
set wildmenu
set wildmode=longest:list,full

"Show partial vim cmd at bottom right
set showcmd

"Highlight matched items
set hlsearch

"Toggle highlighted text
nnoremap <leader>l :noh<CR>

" Shortcutting split navigation, saving a keypress:
map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-k> <C-w>k
map <C-l> <C-w>l

"Case insensitive search
set ignorecase

"Unless capital letters used
set smartcase

"Incremental search
set incsearch

"Stops movements going to the start of line
set nostartofline

"Always display status line
set laststatus=2

"Display cursor line number
set number

"Display line numbers relative to cursor
set relativenumber

"Display as much as possible of line that doesn't fit
set display+=lastline

"Nice colour theme
colo my-slate

"Don't wrap a line in the middle of a word
set linebreak

"Keep 1 lines above/below cursor
set scrolloff=1

"Keep 5 cols left/right of cursor if nowrap on
set sidescrolloff=5

"Fold on indents
set foldmethod=syntax

"Fold off by default
set nofoldenable

"Toggle folding
nnoremap <leader>f :setlocal foldenable!<CR>

"Auto re-read files if changed but unmodified in vim
set autoread

"Toggle spell checking
nnoremap <leader>s :setlocal spell! spelllang=en_au<CR>

"Change local spell highlighting to orange
hi SpellLocal ctermbg=208

"Change where vim puts files
set backupdir=$HOME/.vim/backup//
set directory=$HOME/.vim/swap//
set undodir=$HOME/.vim/undo//

"Save vim history on exit
" '10  :  marks will be remembered for up to 10 previously edited files
" "100 :  will save up to 100 lines for each register
" :20  :  up to 20 lines of command-line history will be remembered
" %    :  saves and restores the buffer list
" n... :  where to save the viminfo files
set viminfo='10,\"100,:20,%,n~/.viminfo

""Function that restores the cursor
function! ResCur()
  if line("'\"") <= line("$")
    normal! g`"
    return 1
  endif
endfunction
"Call the function above on enter
augroup resCur
  autocmd!
  autocmd BufWinEnter * call ResCur()
augroup END

"Enable undo on return to vim
set undofile

"Add dictionary spelling to completion when spelling on
set complete+=k
set dictionary+=/usr/share/dict/british-english

"Adding thesaurus
set thesaurus+=/home/en0cs/Documents/thesaurus.txt

"Open files in current vim directory
autocmd BufEnter * cd %:p:h

"Add auto new list item
set com=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,b:-
set formatoptions+=roln

" Compile document, be it LaTeX/markdown/etc.
map <leader>c :w! \| !compiler <c-r>% tmp<CR>

" Open corresponding .pdf/.html or preview
map <leader>, :!opout <c-r>% tmp<CR><CR>

"Set tags file location
set tags+=$HOME/.vim/tags

"Auto compile tags
nnoremap <leader>t :!ctags -f ~/.vim/tags --tag-relative=yes -R ./*<CR>

"Todo
autocmd BufRead,BufNewFile .todo set autoindent
autocmd BufRead,BufNewFile .todo set cursorline
function! DoneToggle()
	s/^\(\s*\)- /\1[@]/e 1
	s/^\(\s*\)⚫/\1- /e 1
	s/^\(\s*\)\[@\]/\1⚫/e 1
endfunc
autocmd BufRead,BufNewFile .todo nnoremap <CR> :call DoneToggle()<CR>:noh<CR>j$

"Notepad
autocmd BufRead,BufNewFile .notepad set autoindent
autocmd BufRead,BufNewFile .notepad set cursorline

"Markdown
autocmd Filetype markdown set autoindent
autocmd Filetype markdown set formatoptions+=roln
autocmd Filetype markdown set com=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,b:-,b:+,b:*,b:1.5

"Automatically deletes all trailing whitespace and newlines at end of file on save
autocmd BufWritePre * %s/\s\+$//e
autocmd BufWritepre * %s/\n\+\%$//e
