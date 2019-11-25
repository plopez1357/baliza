#include <Arduino.h>
#include "unity.h"
#include "APIService.h"

APIService apiService;

void findJsonState(void) {
  String json = "{ '@type': 'builds', '@href': '/repo/26853908/builds?limit=1', '@representation': 'standard', '@pagination': { 'limit': 1, 'offset': 0, 'count': 8, 'is_first': true, 'is_last': false, 'next': { '@href': '/repo/26853908/builds?limit=1&offset=1', 'offset': 1, 'limit': 1 }, 'prev': null, 'first': { '@href': '/repo/26853908/builds?limit=1', 'offset': 0, 'limit': 1 }, 'last': { '@href': '/repo/26853908/builds?limit=1&offset=7', 'offset': 7, 'limit': 1 } }, 'builds': [ { '@type': 'build', '@href': '/build/613510953', '@representation': 'standard', '@permissions': { 'read': true, 'cancel': true, 'restart': true }, 'id': 613510953, 'number': '8', 'state': 'statusTest', 'duration': 35, 'event_type': 'push', 'previous_state': 'passed', 'pull_request_title': null, 'pull_request_number': null, 'started_at': '2019-11-18T13:45:56Z', 'finished_at': '2019-11-18T13:46:31Z', 'private': false, 'repository': { '@type': 'repository', '@href': '/repo/26853908', '@representation': 'minimal', 'id': 26853908, 'name': 'prueba', 'slug': 'plopez1357/prueba' }, 'branch': { '@type': 'branch', '@href': '/repo/26853908/branch/master', '@representation': 'minimal', 'name': 'master' }, 'tag': null, 'commit': { '@type': 'commit', '@representation': 'minimal', 'id': 186359576, 'sha': '1e1f62ea414e024804369e0238266050da4915c6', 'ref': 'refs/heads/master', 'message': 'Commit13', 'compare_url': 'https://github.com/plopez1357/prueba/compare/e71d288bc2c9...1e1f62ea414e', 'committed_at': '2019-11-18T13:45:18Z' }, 'jobs': [ { '@type': 'job', '@href': '/job/613510954', '@representation': 'minimal', 'id': 613510954 } ], 'stages': [ ], 'created_by': { '@type': 'user', '@href': '/user/1827891', '@representation': 'minimal', 'id': 1827891, 'login': 'plopez1357' }, 'updated_at': '2019-11-18T13:46:31.497Z' } ] }";
  String state = apiService.findStateOfTheJson(json);
  TEST_ASSERT_EQUAL_STRING(('statusTest'), (state.c_str));
}

// setup connects serial, runs test cases (upcoming)
void setup() {
  delay(1000);

  UNITY_BEGIN();
  RUN_TEST(findJsonState);
  UNITY_END();
}


void loop() {
  // nothing to be done here.
}
