				Minishell

Functions:

	-> access :
		`access` is a function used to check whther a file exists and to test for the accessibility of the file. it take two arguments, the name of file and the mode of access.
			``` int access(const char *path, int mode) ```
		path: argument ponter to a string that contains the name of file you want to check.
		mode: argument is an integer that soecifies the type of access you want to check for.
			the following values can be used for the `mode`:
				`F_OK`: tests for the exitence of the file.
				`R_OK`: tests for read permission.
				`W_OK`: tests for write permission.
				`X_OK`: tests for execute permission.
		RETURN: the `access` function returns 0 if the requested access is allowed, or -1 if it is not allowed.
	
	-> fork :
		`fork` is a system call in Unix-based operating systems that creates a new process by duplicationg the calling process, and the original process is called the parent proccess. after `fork` is called, both the parent and child processes execute the same code starting from the next instruction following the `fork` call.
			``` pid_t fork(void) ```
		RETURN: the `fork` function return a value of type pid_t, which is a signed integer type that represents the process ID (PID) of the child process in the parent process, and 0 in the child process. if `fork` fails, it return -1.
	
	-> wait : 
		`wait` function used to wiat for a child process to tarminate and obtain its termination status. it takes a pointer to an integer variable where the termination status will be stored as an argument.
			``` pid_t wait(int *status) ```
		status: the `status` argument pointer to an integer variable that will be used to store the termination status of the child process.
		RETURN: the function return the process ID of the terminated child process, or -1 if an error occurs.
	
	-> waitpid :
		`waitpid` is a system call in the C programming language that waits for a child process to change its state. it is used to synchronize the parent and child processes and to retrieve the exit status of a child process.
			``` pid_t waitpid(pid_t pid, int *status, int options) ```
		pid: the `pid` argument specifies the process ID of the child process to wait for. if `pid` is negative, `waitpid` waits for any child process whose process group ID is equal to the absolute value of `pid`. if `pid` is zero, waits for any child process whose process group ID is equal to the of the calling process. if `pid` is positive, waits for the child process whose process ID is equal to `pid`.
		status: the `status` argument is a pointer to an integer variable in which the exit status of the child process is stored. if `status` is `NULL`, the exit status is not retrieved.
		options: the `options` argument specifies various options for the `waitpid` function. the commonly used options are `WUNTRACED` and `WCONTINUED`, which respectively cause `waitpid` to return when a child process is stopped or continued.
		RETURN: the return value of `waitpid` is the process ID of child process that change state, or -1 if an error accurred.

	-> wait3 :
		in C programming, `wait3` is a sistem call used to wait for any child process to terminate and retrieve information about its resource usage. the `wait3` fucntion is similar to `waitpid`, but provides additional information about child process's resource usage. 
			``` pid_t wait3(int *status, int options, struct rusage *usage) ```
		status: a pointer to an integer where the status of the terminated child process is stored.
		options: a set of options that control the behavior of the function. the option can include `WNOHANG` to return immediately if no child process has terminated, `WUNTRACED` to report the status of child processes that have been stopped, and `WCONTTNUED` to report the status of child processes that have benn resumed.
		usage: a pointer to a `struct rusage` the stores information about the resources used by the child process.

	-> execve :
		`execve` is a function in C that allows a process to replace its current program image with a new one. it is often used to execute a different program, with different arguments and environment variables.
			``` int execve(const char *path, char * const argv[], char * const envp[]) ```
		path: a path name that identifies the new process image file.
		argv: an array of character pointers to NULL-terminated strings. your application must ensure that the last member of this array is a NULL pointer. these strings constitute the argument list available to the new process image. the value is `argv[0]` must point to a filename that's associated with the process being started.
		envp: an array of character pointers to NULL-terminated strings. these strings constitute the environment for the new process image. terminate the envp array with a NULL pointer.
		RETURN: the `execve` does not return if it  is successful. or in case of an error `execve` return -1 and set type of error in global variable `errno`.
	
	-> readline :
		`readline` will read a line from the terminal and return it, using prompt as prompt. if prompt is NULL or the empty string, no prompt is issued. the line returned is allocated with malloc. the caller must free it when finished. the line returned has the final newline removed, so only the text of the line remains.
			``` char *readline(const char *prompt) ```
		prompt: the text to show to the user in terminal as prompt.
		RETURN: `readline` return the text of the line read. a blank line returns the empty string. if EOF is encountered while reading a line, and the line is empty, NULL is returned.
	
	-> add_history :
		`add_histroy` is a fucnction provided by the `readline` library in C, which is used to add a line of text to the history list.
			``` void add_history(const char *input) ```
		input: the `input` is the line readed from terminal using `readline` function, pass it here to added to the history list.
		
	-> rl_clear_histroy :
		`rl_clear_history` is a function provided by the `readline` library in C, which is used to clear the history list of previously entered input.
			``` void rl_clear_history(void) ```
	
	-> rl_replace_line :
		`rl_replace_line` is a fucntion provided by the `readline` library in C, which is used to replace the current input line with a new string.
			``` void rl_replace_line(const char *new_input, int flag) ```
		new_input: replace the `prompt` of `readline` function with `new_input`.
		flag: I dont know it, but pass 0 to it.

	-> rl_on_new_line :
		`rl_on_new_line` is a fucntion provided by the `readline` library in C, which used to move the cursor to the beginning of a new line.
			``` void rl_on_new_line(void) ```
	
	-> rl_redisplay : 
		`rl_redisplay` is a fucntion provided by the `readline` library in C that allows you to force the display to be update with the current input line. this can be useful when you need to modify the input line in response to some event or condition, and you want to make sure that the update input line is immediately displayed to the user.
			``` void rl_redisplay() ```
	
