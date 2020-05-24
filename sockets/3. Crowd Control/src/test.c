// Project source
#include "client_handler.c"

// Project headers
#include "settings.h"
#include "client_t.h"

// Standard C Libraries
#include <string.h>

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
  // set_clients(test_clients);

  // Test get_free_client
  assert_true(get_free_client() == expected_index);
}

// Mocked read function
int __wrap_read(int sock, void * buf, int buf_len)
{
  // Assert parameter values
  assert_int_equal(sock, (int) mock());               // sock parameter
  assert_non_null(buf);                    // buf parameter
  assert_int_equal(buf_len, (int) mock());  // buf_len parameter

  // Send mocked request
  strcpy((char *) buf, (char *) mock());

  // Return number of returned characters
  return (int) mock();
}

// Mocked write function
int __wrap_write(int sock, void * buf, int buf_len)
{
  return (int) mock();
}


static void test_handle_client_requests()
{
  // Set designated client index for testing
  int expected_index = 2;

  // Init mocked clients array
  client_t test_clients[MAX_NUM_CLI];
  for(int x = 0; x < MAX_NUM_CLI; x++)
  {
    // Generate client name
    char name[3];
    sprintf(name, "%.3d", x);

    // Set client attributes
    test_clients[x].conn = x;
    strcpy(test_clients[x].name, name);
  }

  // Assign clients pointer to test clients array
  clients = test_clients;
  // set_clients(test_clients);

  // Create placeholder for mocked client name
  char name[3];
  sprintf(name, "%.3d", expected_index);

  // Init mocked client
  client_t test_client = test_clients[expected_index];

  // Create placeholder for mocked request
  char * test_req = "004 hello friend";

  // Setup expected values for mock read()
  will_return(__wrap_read, test_clients[expected_index].conn);  // sock parameter
  will_return(__wrap_read, MAX_MSG_LEN);                        // buf_len parameter
  will_return(__wrap_read, test_req);                           // mocked request
  will_return(__wrap_read, strlen(test_req));                   // return value

  // Setup expected values for mock write()
  will_return(__wrap_write, -1);

  // Run function
  handle_client_requests(&test_client);

}

int main()
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_get_free_client),
    cmocka_unit_test(test_handle_client_requests),
  };

  // done
  return cmocka_run_group_tests(tests, NULL, NULL);
}
