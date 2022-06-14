#ifndef __ERROR_PAGE_GENRATOR_HPP__
#define __ERROR_PAGE_GENRATOR_HPP__

#include <string>

static const char *templte =	"<!DOCTYPE html>"
						"<html>"
						"<style>"
						"h1 {text-align: center;}"
						"p {text-align: center;}"
						"</style>"
						"<head>"
						"<title>error</title>"
						"</head>"
						"<body>"
						"<h1>%d</h1>"
						"<p>%s</p>"
						"</body>"
						"</html>";
std::string	ErrorPageGenerator (unsigned short code);

#endif