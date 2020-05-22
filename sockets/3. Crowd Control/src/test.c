// Project source
#include "client_handler.c"

// Project headers
#include "settings.h"
#include "client_t.h"

// CMocka libraries
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_get_free_client()
{
  // Set correct answer from function
  int expected_index = 0;

  // Init clients array
  client_t test_clients[MAX_NUM_CLI];
  for(int x = 0; x < MAX_NUM_CLI; x++)
  {
    if(x == expected_index) test_clients[x].conn = -1;
    else test_clients[x].conn = 123;
  }

  // Assign clients pointer to test clients array
  clients = test_clients;

  // Test get_free_client
  assert_true(get_free_client() == expected_index);
}

int main()
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_get_free_client),
  };

  // done
  return cmocka_run_group_tests(tests, NULL, NULL);
}
