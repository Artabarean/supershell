# Minishell – Test Checklist

Este documento recoge las pruebas funcionales y de parsing realizadas durante el desarrollo de **minishell**, así como los fallos detectados y casos pendientes. Está pensado para trabajo colaborativo y revisión continua.

---

## 1. Prompt y ciclo general

* [x] El prompt aparece correctamente
* [x] Se repite tras cada comando
* [x] Línea vacía no cierra la shell
* [x] `exit` sin argumentos cierra con código 0
* [x] `exit 42` cierra con código 42
* [x] EOF en vacío (Ctrl-D) cierra la shell

**Notas técnicas**:

* `g_exit_status` siempre actualizado por el padre (`pid_stat`).
* Mensajes de error o warnings impresos por el padre, no por handlers.

### Pendiente

* `export`
* `unset`
* Manejo correcto de códigos de salida en errores (ej. `cd $PWD hi` → exit code 1)
* Mensajes de error en `exit`

---

## 2. Comandos básicos y espacios

* [x] `ls -la`
* [x] `ls -la /tmp`
* [x] `echo hola`
* [x] `echo ""`
* [x] `echo ''`
* [x] `echo "a b c"`
* [x] `echo a\ b\ c`

---

## 3. Comillas simples y dobles

* [x] `echo "hola mundo"`
* [x] `echo 'hola mundo'`
* [x] `echo "hola 'mundo'"`
* [x] `echo 'hola "mundo"'`
* [x] `echo "hola"mundo`
* [x] `echo 'hola'mundo`
* [x] `echo "a'b"c`
* [x] `echo '"hola"'`
* [x] `echo "'hola'"`
* [x] `echo "hola`
* [x] `echo 'hola`

---

## 4. Pipes

### Correctos

* [x] `ls | wc`
* [x] `cat file | grep a | wc -l`
* [x] `echo hola | cat | cat | cat`
* [x] `ls|wc`
* [x] `ls |wc`
* [x] `ls| wc`

### Incorrectos (errores sintácticos)

* [x] `|`
* [x] `||`
* [x] `| ls`
* [x] `ls || wc` (no implementamos `||`)
* [x] `ls | | wc`
* [x] `ls | | | wc`
* [ ] `ls |` (en bash queda abierto)
* [x] `echo hola | |`

---

## 5. Redirecciones 

## Simples

* [x] `echo hola > file`
* [x] `echo hola >> file`
* [x] `cat < file`
* [x] `cat < input > output`
* [x] `cat >out <in`
* [x] `cat <<< EOF`

## Complejas

* [ ] `echo hi>./outfiles/outfile01 | echo bye`
* [ ] `echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye`
* [ ] `echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02`
* [ ] `ls >>./outfiles/outfile01`
* [ ] `ls >>      ./outfiles/outfile01`
* [ ] `ls >>./outfiles/outfile01 >>./outfiles/outfile02`
---

## 6. Redirecciones incorrectas

* [x] `echo hola >`
* [x] `echo hola >>`
* [x] `cat <`
* [x] `echo > > file`
* [x] `echo >>> file`
* [x] `cat <<<< EOF`
* [x] `echo < > file`
* [x] `echo >> < file`

---

## 7. Heredoc

* [ ] `cat << EOF`
* [ ] `cat <<EOF`
* [ ] `cat << "EOF"`
* [ ] `cat << 'EOF'`
* [ ] `cat <<EOF | wc`

### Delimitador con comillas

* [ ] `cat << "END"`
* [ ] `cat << 'END'`
* [ ] `cat << "EOF" | grep x` → no ejecuta el segundo comando

---

## 8. Variables y expansión (parsing, sin expandir aún)

* [x] `echo $USER`
* [x] `echo "$USER"`
* [x] `echo '$USER'` → fallo al ejecutar (no debe expandir)
* [x] `echo "hola $USER mundo"`
* [x] `echo $$$$`
* [x] `echo "'$USER'"`
* [ ] `echo $UNSET_VARIABLE`
* [x] `echo $?????????`
* [x] `echo "hola $meru"`

---

## 9. Secuencias complejas de operadores

* [ ] `echo hola > file1 | cat`
* [ ] `echo hola | cat > file1`
* [ ] `cat < in | grep a > out`
* [ ] `cmd1 | cmd2 < in | cmd3 > out`
* [ ] `cmd1 > out1 | cmd2 > out2`
* [ ] `cmd < in << EOF`
* [ ] `cmd <<EOF > out`

---

## 10. Casos de espacios raros

* [ ] `echo hola>file`
* [ ] `echo hola>>file`
* [ ] `echo hola<file`
* [ ] `echo "<<EOF"`
* [ ] `echo >file`
* [ ] `> file echo hola` (debería ser error)
* [ ] `cat<in>out`
* [ ] `cmd<<EOF|wc`
* [ ] `cmd>out|cmd2<in`

---

## 11. Splitting (detección de fallos)

* [ ] `echo foo"bar"baz`
* [ ] `echo foo'bar'baz`
* [ ] `echo "foo"'bar'"baz"`
* [ ] `echo """"` (cadena vacía)
* [ ] `echo ''""''`
* [ ] `echo " "`

---

## 12. Errores combinados

* [x] `| <`
* [x] `> |`
* [x] `<< |`
* [x] `| >`
* [x] `<<` (sin delimitador)

---

## 13. Wildcards (solo parsing)

* [ ] `echo *`
* [ ] `echo a*`
* [ ] `echo *a`
* [ ] `echo *.*`
* [ ] `ls * | wc`
* [ ] `echo "*"`
* [ ] `echo "*a*"`

---

## 14. Comprobaciones generales

* [ ] FDs cerrados correctamente en cada hijo
* [ ] Status final es el del último comando
* [ ] `>` crea o trunca archivo
* [ ] `>>` añade al archivo
* [ ] `<` falla si no puede leer archivo
* [ ] `<<` sin comillas expande variables
* [ ] `<<` con comillas no expande
* [ ] Ctrl-C durante heredoc cancelado correctamente
* [ ] Sin leaks en valgrind
* [ ] Sin `still reachable`
* [ ] Sin invalid reads/writes
* [ ] Libera memoria en errores
* [ ] Gran número de pipes
* [ ] Wildcard con miles de archivos

---

## 15. Builtins y ejecución

* [x] `echo hola`
* [x] `echo -n hola`
* [x] `echo "a b c"`
* [x] `cd carpeta`
* [x] `cd` (HOME)
* [x] `cd -`
* [x] Actualiza `PWD` y `OLDPWD`
* [ ] `export VAR=valor`
* [ ] `export` lista ordenada
* [ ] Manejo de nombres inválidos
* [ ] `unset` elimina variable
* [ ] `exit N` con N válido
* [ ] Error en `exit 1 2` (demasiados argumentos)
* [ ] Detecta valores no numéricos en `exit`
* [ ] Búsqueda en `PATH`
* [ ] Ruta absoluta (`/bin/ls`)
* [ ] Ruta relativa (`./a.out`)
* [ ] Error de permisos
* [ ] Error si no existe
* [x] Ctrl-C limpia línea y muestra prompt
* [x] Ctrl-\ ignorado en shell
* [ ] Ctrl-C afecta solo a hijos
* [x] Ctrl-D en heredoc finaliza heredoc
