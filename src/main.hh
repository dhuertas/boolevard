/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __MAIN_HH__
#define __MAIN_HH__

#define LOG_INFO 0
#define LOG_DEBUG 1

extern int logLevel_;

#define INFO(fmt, ...) do { \
  if (logLevel_ >= LOG_INFO) \
    fprintf(stdout, fmt "\n", ##__VA_ARGS__); } while(0)

#define DEBUG(fmt, ...) do { \
  if (logLevel_ >= LOG_DEBUG) \
    fprintf(stdout, fmt "\n", ##__VA_ARGS__); } while(0)


#endif