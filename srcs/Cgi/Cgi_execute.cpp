//
// Created by Mouaad Labhairi on 6/1/22.
//

#include <iostream>
#include "Cgi_execute.hpp"
#include <fcntl.h>
#include <unistd.h>
#include "../ServerConfiguration/Configuration.hpp"
#include "../Request/HeaderFields.hpp"
#include "Cgi_parser.hpp"
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>



Cgi_execute::Cgi_execute(dataConnection *context, std::string& path, std::string& exec) : _context(context), _path(path), _exec(exec){
	this->flags = 0;
	this->buf = NULL;
}

char **Cgi_execute::fill_env(std::map<std::string, std::string> env_map)
{
	char **env;
	int i = 0;
	std::string temp;

	env = (char **)malloc(sizeof (char *) * (env_map.size() + 1));
	for (std::map<std::string, std::string>::iterator it = env_map.begin(); it != env_map.end(); it++)
	{
		env[i] = (char *) malloc(sizeof (char ) * (it->first.length() + 1 + it->second.length()) + 1);
		temp = it->first;
		temp += "=";
		temp += it->second;
		std::copy(temp.begin(), temp.end(), env[i]);
		env[i][temp.length()] = '\0';
		i += 1;
	}
	env[i] = NULL;
	return env;
}

std::string Cgi_execute::gen_random(const int len) {
	static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_s;
}

void alarm_handler(int seg)
{
	(void)seg;
	kill(getpid(), SIGINT);
}
void 	Cgi_execute::cgi_method_get(void ) {

	pid_t	pid;
	URI uri = _context->getRequest()->get_requestLine()->getURL();
	uri.ressource();
	std::string url(uri._ressource.begin() + 1, uri._ressource.end());
	OutputBuffer output = _context->getOutputBuffer();
	char	**env;
	env_map = set_environment_variables(_context);

	char *argv[3];
	int check;
	char *path;
	int fd1;


//	if (env_map["Content-Type"].empty())
//		flags = 415;
	if (!uri._query.empty())
	{
		fd1 = ::open(".message_body.txt", O_CREAT | O_TRUNC| O_RDWR, 0666);
		if (write (fd1, uri._query.c_str(), uri._query.size()) == -1)
			flags = 500;
		close (fd1);
		fd1 = ::open(".message_body.txt", O_RDONLY, 0666);
		if (fd1 == -1)
			flags = 500;
		env_map["QUERY_STRING"] = uri._query;
	}
	pipe(fd);
	env = fill_env(env_map) ;
	argv[0] = strdup(_exec.c_str());
	argv[1] = strdup(_path.c_str());

//	argv[0] = strdup("/usr/bin/python3");
//	argv[1] = strdup("/Users/molabhai/Desktop/Web_Server/cgi-bin/set_cookies.py");
	argv[2] = NULL;
	pid = fork();
	if (pid < 0)
		flags = 500;
	else if (pid == 0)
	{
		signal(SIGALRM, alarm_handler);
		for(int i = 0 ; env[i] ; i++)
			putenv(env[i]);
		close(this->fd[0]);
		dup2(fd1, 0);
		close(fd1);
		dup2(this->fd[1], 1);
		close(this->fd[1]);
		path = strdup(_exec.c_str());
//		path = strdup("/usr/bin/python3");
		ualarm(5 * 1e6, 0);
		if ((check = execve(path, argv, env)) == -1)
		{
			flags = 500;
			std::cout << "Error in exec\n"; 
			exit(EXIT_FAILURE);
		}
	}
	close(fd[1]);
	waitpid(pid, NULL, WNOHANG);
	ualarm(0,0);
}

void	Cgi_execute::add_response_variables(URI uri)
{
	this->env_map["SERVER_NAME"] = "web_server";
	this->env_map["PATH_INFO"] = uri._ressource;
}

void 	Cgi_execute::cgi_method_post(void ) {

	pid_t	pid;
	URI uri = _context->getRequest()->get_requestLine()->getURL();
	uri.ressource();
	std::string url(uri._ressource.begin() + 1, uri._ressource.end());
	OutputBuffer output = _context->getOutputBuffer();
	char	**env;
	char *argv[3];
	int check;
	char *path;
	int fd1 = ::open(".message_body.txt", O_CREAT | O_TRUNC| O_RDWR, 0666);
	if (fd1 == -1)
		flags = 500;
	if (write (fd1, this->messageBody.c_str(), messageBody.size()) == -1)
		flags = 500;
	close (fd1);
	fd1 = ::open(".message_body.txt", O_RDONLY,0666);
	if (pipe(fd) == -1)
		flags = 500;
	env = fill_env(env_map);
	argv[0] = strdup(_exec.c_str());
	argv[1] = strdup(_path.c_str());

//	argv[0] = strdup("/usr/bin/python3");
//	argv[1] = strdup("/Users/molabhai/Desktop/Web_Server/cgi-bin/set_cookies.py");
	argv[2] = NULL;
	int flag = fcntl (fd[0], F_GETFL);
	flag |= O_NONBLOCK;
	fcntl (fd[0], F_SETFL, flag);
	pid = fork();
	if (pid == -1)
		flags = 500;
	if (pid == 0)
	{
		signal(SIGALRM, alarm_handler);
		for(int i = 0 ; env[i] ; i++)
			putenv(env[i]);
		close(this->fd[0]);
		dup2(fd1, 0);
		close(fd1);
		dup2(this->fd[1], 1);
		close(this->fd[1]);
		path = strdup(_exec.c_str());
//		path = strdup("/usr/bin/python3");
		ualarm(5 * 1e6, 0);
		if ((check = execve(path, argv, env)) == -1)
		{
			flags = 500;
			std::cout << "Error in exec\n"; 
			exit(EXIT_FAILURE);
		}
	}
	close(fd[1]);
	waitpid(pid, NULL, WUNTRACED);
	ualarm(0,0);

}

void	Cgi_execute::cgi_execute()
{
	env_map = set_environment_variables(_context);
	std::string value = this->env_map["REQUEST_METHOD"];
	if (value == "GET")
		cgi_method_get();
	else if (value == "POST")
		cgi_method_post();
	else
		flags = 501;
}

Response	*Cgi_execute::cgi_response(void )
{
	std::map<std::string, std::string> cookies_map;
//	std::string stringtmp;
	this->cgi_execute();
	char *temp = (char *)calloc(sizeof(char), 101);
	int len = 0;
	int ret;

	while ((ret = read(fd[0], temp, 100)))
	{
		if (strcmp(temp, "Error in exec\n") == 0)
		{
			flags = 500;
			break;
		}
		len += strlen(temp);
		if (buf)
		{
			char *tmp = strdup(buf);
			free (buf);
			buf = (char *) calloc(sizeof (char ) , len + 1);
			strcat(buf, tmp);
			strcat(buf, temp);
			free(tmp);
			free(temp);
			temp = (char *)calloc(sizeof(char), 101);
		}
		else if (len > 0)
		{
//			buf  = new char[len + 2];
			buf = (char *) calloc(sizeof (char ) , len + 1);
			strcat(buf, temp);
			free(temp);
			temp = (char *)calloc(sizeof(char), 101);
		}
	}
	if (ret < 0)
		flags = 500;
	close(this->fd[0]);
	if (temp)
		delete temp;
	if (flags != 0)
	{
		free(buf);
		return  NULL;
	}
	Cgi_parser cgiParser(buf, _context);
	if (buf)
		free(buf);
	cgiParser.parsing_cgi_response();
	cookies_map = cgiParser.get_cookies();
	Response *res = _context->getResponse();
	res->setVersion("HTTP/1.1");
	res->setStatusCode(std::to_string(cgiParser.get_status()));
	res->setReasonPhrase(cgiParser.get_reason_phrase());
	res->addHeaderField("Content-Type", cgiParser.get_content_type());
	res->addHeaderField("Location", cgiParser.get_location());
	res->addHeaderField("Content-Length", cgiParser.get_content_type());
	res->getPayload().setBuffer(cgiParser.get_message_body());

	return (res);
}

int 	Cgi_execute::get_flags ()
{
	return flags;
}


Cgi_execute::~Cgi_execute() {}