
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>


// Define ANSI escape sequences for colors and styles
#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int main()
{
	size_t start, end;
	start = get_current_time();
	ft_usleep(200);
	end = get_current_time();
	size_t time = end - start;

	printf("Expected sleep duration: "BOLD_CYAN"\t200 milliseconds\n"RESET);
    printf("Actual sleep duration: "BOLD_CYAN"\t\t%zu milliseconds\n\n"RESET, time);
}
