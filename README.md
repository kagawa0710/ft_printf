# ft_printf

## メモ

```bash
gcc -c ft_printf_tmp.c -o ft_printf_tmp.o
make -C ./libft
cp libft/libft.a libftprintf.a
ar rcs libftprintf.a ft_printf_tmp.o
nm -s libftprintf.a
gcc -g main_tmp.c libftprintf.a
```

GCC で静的リンク時のライブラリ指定の順番には依存性がある。呼び出される側のライブラリーは「後で」リンクする必要があり注意が必要。この指定がうまくいっていないときは「undefined reference エラー」がでる。

デバッグしたい時は以下のコマンドが楽

```bash
make && gcc -g -fsanitize=address main.c libftprintf.a && ./a.out && make fclean > /dev/null
```
# ft_printf
