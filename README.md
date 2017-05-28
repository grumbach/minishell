# minishell

	$> A computer is like air conditioning
	It becomes useless when you open Windows.
								Linus Torvalds

Let us therefore write a <b>UNIX</b>-like shell : <b>minishell</b>

### built-ins:
- echo
- cd
- setenv
- unsetenv
- env
- exit


### used funcs:
- malloc, free
- access
- open, close, read, write
- opendir, readdir, closedir
- getcwd, chdir <-
- stat, lstat, fstat ?
- fork, execve <-
- wait, waitpid, wait3, wait4 <-
- signal, kill
- exit

execve (/bin/ls, -hj -f dt ,env) -1FAIL
access (path, W_OK | X_OK | R_OK | F_OK) // F_OK == exist
wait()


// echo [-n(no\n)] [string ...]
// cd [-(goback)] [dir]
// setenv PATH="/bin:/usr/bin:/usr/sbin:usr/ucb/bin"
// unsetenv PATH
// envp
// exit
