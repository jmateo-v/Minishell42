# Minishell42

Implementacion modular de un shell tipo POSIX inspirado en bash. El objetivo es reproducir el comportamiento basico del interprete original, respetando la gestion de senales, los builtins y la expansion de tokens, ademas de la version bonus con operadores logicos y wildcards.

## Tabla de contenidos
1. [Resumen rapido](#resumen-rapido)
2. [Caracteristicas principales](#caracteristicas-principales)
3. [Requisitos](#requisitos)
4. [Compilacion](#compilacion)
5. [Ejecucion y uso](#ejecucion-y-uso)
6. [Comportamiento del shell](#comportamiento-del-shell)
7. [Arquitectura](#arquitectura)
8. [Componentes clave](#componentes-clave)
9. [Bonus y extensiones](#bonus-y-extensiones)
10. [Depuracion y tests](#depuracion-y-tests)
11. [Creditos](#creditos)

## Resumen rapido
- Binario principal: `./minishell`
- Entrada interactiva usando `readline`
- Estructura de datos principal: lista enlazada de `t_cli`
- Librerias internas: `libft/` y `get_next_line/`
- Compatibilidad con Linux y macOS con soporte `readline`

## Caracteristicas principales
- Tokenizacion segura con comillas simples/dobles, escape, operadores `|`, `>`, `>>`, `<`, `<<`.
- Expansion de variables de entorno y del valor de salida (`$?`).
- Parsing de pipelines y redirecciones hacia estructuras listas para ejecutar.
- Ejecucion de comandos externos con `fork` + `execve` y manejo transparente de `PATH`.
- Builtins integrados: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Heredocs con expansion condicional de variables y soporte de `Ctrl+C` acorde a bash.
- Manejo de senales interactivo (`SIGINT`, `SIGQUIT`) tanto para el prompt como para procesos hijos.
- Bonus: operadores logicos `&&`, `||`, parentesis y expansion de `*` (wildcards) para argumentos.

## Requisitos
- Compilador C compatible con el estandar GNU99 (probado con `cc`/`clang`).
- `make` (GNU Make 3.81+).
- Libreria `readline` y encabezados de desarrollo (`libreadline-dev` en Debian/Ubuntu, `readline` via Homebrew en macOS).
- Entorno POSIX (Linux x86_64 o macOS). No se garantiza compatibilidad en Windows nativo.

## Compilacion
```bash
make            # compila minishell clasico
make bonus      # compila minishell_bonus con logica y wildcards
make clean      # elimina objetos
make fclean     # elimina binarios y objetos
make re         # recompila desde cero
```
El `Makefile` vincula automaticamente `libft` y `get_next_line`, por lo que no se requieren pasos extra.

## Ejecucion y uso
```bash
./minishell
```
Comandos de ejemplo:
```bash
minishell$ echo "Hola mundo"
minishell$ export PATH=/usr/bin
minishell$ ls -l | grep minishell
minishell$ cat <<EOF | grep Hola
minishell> Hola
minishell> EOF
```
Para salir: `Ctrl+D` o el builtin `exit [status]`.

## Comportamiento del shell
- **Prompt y senales:** `shell_loop.c` configura handlers para que `Ctrl+C` solo resetee la linea actual y no cierre el shell.
- **Variables de entorno:** `shell_env.c` inicializa un listado enlazado `t_shenv`. Los builtins `export` y `unset` modifican dicha estructura y mantienen `PWD`/`OLDPWD` actualizados.
- **Estado de salida:** la variable global `g_status` conserva el ultimo codigo de retorno. Se expone a los usuarios via `$?` y se reutiliza para logica condicional en el bonus.
- **Heredocs:** `parsing/handle_heredoc.c` y `exec/exec_heredoc/` crean archivos temporales o pipes anonimos, respetando la expansion solo si el delimitador no esta entre comillas.

## Arquitectura
```
.
?? minishell.c              # punto de entrada
?? shell_*.c                # bucle principal y setup de entorno
?? tokenizing/              # separacion, expansion y validacion de tokens
?? parsing/                 # construccion de nodos t_cli con redirecciones
?? exec/                    # ejecucion, pipelines, builtins, heredocs
?  ?? builtins/             # implementacion individual de cada builtin
?  ?? exec_pipe/            # gestion de pipes y procesos hijos
?  ?? exec_heredoc/         # lectura y expansion de heredocs
?? signals/                 # handlers y configuraciones por contexto
?? utils/                   # helpers de memoria, strings y loop interactivo
?? libft/                   # libreria auxiliar (printf, strings, listas...)
?? get_next_line/           # utilidades de lectura bufferizada
```

## Componentes clave
- `minishell.c`: inicializa `t_shenv` via `ft_setup_shell`, entra al `shell_loop` y limpia recursos.
- `shell_loop.c`: integra `readline`, agrega entradas al historial y delega el procesamiento de cada linea.
- `tokenizing/`: `tokenizer.c` divide la linea en segmentos, `token_expansion/` reemplaza variables y `token_error.c` asegura que la sintaxis sea valida antes de parsear.
- `parsing/parsing.c`: crea nodos `t_cli` con sus redirecciones, argumentos y heredocs. Bonus agrega parentesis y logica booleana.
- `exec/ft_execute.c`: decide si ejecutar builtins en el padre o lanzar procesos con pipelines usando `exec_pipe/`.
- `exec/builtins/*.c`: implementaciones fieles a bash, respetando side effects (`cd` actualiza `PWD`, `exit` valida argumentos numericos, etc.).
- `signals/`: `sig_manager.c` aplica perfiles de senales (parent, child, heredoc) para replicar bash en cada contexto.

## Bonus y extensiones
- **Wildcards `*`:** directorios y archivos se expanden a partir de `wildcard_collect_bonus.c`, que filtra con patrones implementados en `wildcard_match_bonus.c`.
- **Logica `&&` / `||`:** la tokenizacion bonus (`separator_logic_bonus.c`) reconoce operadores y el parser (`parsing_logic_bonus.c`) construye nodos condicionales que se resuelven en `ft_execute_bonus.c`.
- **Parentesis:** permiten agrupar comandos y evaluar bloques completos con su propio contexto de estado.

## Depuracion y tests
- Ejecutar con `valgrind` o `lldb` para buscar fugas: `valgrind --leak-check=full ./minishell`.
- Activar trazas rapidas con la variable `DEBUG=1` (si se desea, se puede instrumentar `ft_debug_log`).
- Usar los scripts de la comunidad (por ejemplo `https://github.com/mixnorm/minishell_tester`) apuntando al binario `./minishell`.
- Autotest manual: comparar contra `/bin/bash` ejecutando las mismas ordenes y verificando `echo $?`.

## Creditos
Proyecto realizado por estudiantes de 42. Inspirado y alineado con los mandatos oficiales del subject `Minishell`. Aporta referencias adicionales de `bash(1)` y `man readline`.

