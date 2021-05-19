#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <map>

/* Prototypes for our hooks */
static void my_init_hook(void);
static void *my_malloc_hook(size_t, const void *);

/* Variables to save original hooks */
static void *(*old_malloc_hook)(size_t, const void *);

/* Override initializing hook from the C library */
void (*__malloc_initialize_hook)(void) = my_init_hook;

static void
my_init_hook(void)
{
  old_malloc_hook = __malloc_hook;
  __malloc_hook = my_malloc_hook;
}

static void *
my_malloc_hook(size_t size, const void *caller)
{
  void *result;

  /* Restore all old hooks */
  __malloc_hook = old_malloc_hook;

  /* Call recursively */
  result = malloc(size);
  int pid = getpid();
  printf("%d: %p\n", pid, result);

  /* Save underlying hooks */
  old_malloc_hook = __malloc_hook;

  /* printf() might call malloc(), so protect it too */
  printf("malloc(%zu) called from %p returns %p\n",
          size, caller, result);

  /* Restore our own hooks */
  __malloc_hook = my_malloc_hook;

  return result;
}
