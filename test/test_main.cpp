#include <Arduino.h>
#include <unity.h>

#include <APIService.h>
#include <ArduinoJson.h>
#include <Baliza.h>
#include <WiFi.h>

// void setUp(void) {
// }

// void tearDown(void) {
// }

int redLedTest = 21;
int greenLedTest = 5;
int yellowLedTest = 15;
int orangeLedTest = 16;

Baliza balizaTest;

String jsonPassed = R"rawliteral(
    {
    "@type": "builds",
    "@href": "/repo/26882066/builds?limit=1",
    "@representation": "standard",
    "@pagination": {
      "limit": 1,
      "offset": 0,
      "count": 22,
      "is_first": true,
      "is_last": false,
      "next": {
        "@href": "/repo/26882066/builds?limit=1&offset=1",
        "offset": 1,
        "limit": 1
      },
      "prev": null,
      "first": {
        "@href": "/repo/26882066/builds?limit=1",
        "offset": 0,
        "limit": 1
      },
      "last": {
        "@href": "/repo/26882066/builds?limit=1&offset=21",
        "offset": 21,
        "limit": 1
      }
    },
    "builds": [
      {
        "@type": "build",
        "@href": "/build/617982918",
        "@representation": "standard",
        "@permissions": {
          "read": true,
          "cancel": true,
          "restart": true
        },
        "id": 617982918,
        "number": "22",
        "state": "passed",
        "duration": 41,
        "event_type": "push",
        "previous_state": "failed",
        "pull_request_title": null,
        "pull_request_number": null,
        "started_at": "2019-11-28T00:56:13Z",
        "finished_at": "2019-11-28T00:56:54Z",
        "private": false,
        "repository": {
          "@type": "repository",
          "@href": "/repo/26882066",
          "@representation": "minimal",
          "id": 26882066,
          "name": "dyasc-2019",
          "slug": "Jorocha/dyasc-2019"
        },
        "branch": {
          "@type": "branch",
          "@href": "/repo/26882066/branch/master",
          "@representation": "minimal",
          "name": "master"
        },
        "tag": null,
        "commit": {
          "@type": "commit",
          "@representation": "minimal",
          "id": 187785603,
          "sha": "a33d81af3640fd1119acd1cc49be29c2254df2f7",
          "ref": "refs/heads/master",
          "message": "Agrega README",
          "compare_url": "https://github.com/Jorocha/dyasc-2019/compare/2d41f5a689e4...a33d81af3640",
          "committed_at": null
        },
        "jobs": [
          {
            "@type": "job",
            "@href": "/job/617982919",
            "@representation": "minimal",
            "id": 617982919
          }
        ],
        "stages": [
  
        ],
        "created_by": {
          "@type": "user",
          "@href": "/user/1910772",
          "@representation": "minimal",
          "id": 1910772,
          "login": "Jorocha"
        },
        "updated_at": "2019-11-28T00:56:54.612Z"
      }
    ]
  })rawliteral";

String jsonFailed = R"rawliteral(
    {
    "@type": "builds",
    "@href": "/repo/26882066/builds?limit=1",
    "@representation": "standard",
    "@pagination": {
      "limit": 1,
      "offset": 0,
      "count": 22,
      "is_first": true,
      "is_last": false,
      "next": {
        "@href": "/repo/26882066/builds?limit=1&offset=1",
        "offset": 1,
        "limit": 1
      },
      "prev": null,
      "first": {
        "@href": "/repo/26882066/builds?limit=1",
        "offset": 0,
        "limit": 1
      },
      "last": {
        "@href": "/repo/26882066/builds?limit=1&offset=21",
        "offset": 21,
        "limit": 1
      }
    },
    "builds": [
      {
        "@type": "build",
        "@href": "/build/617982918",
        "@representation": "standard",
        "@permissions": {
          "read": true,
          "cancel": true,
          "restart": true
        },
        "id": 617982918,
        "number": "22",
        "state": "failed",
        "duration": 41,
        "event_type": "push",
        "previous_state": "failed",
        "pull_request_title": null,
        "pull_request_number": null,
        "started_at": "2019-11-28T00:56:13Z",
        "finished_at": "2019-11-28T00:56:54Z",
        "private": false,
        "repository": {
          "@type": "repository",
          "@href": "/repo/26882066",
          "@representation": "minimal",
          "id": 26882066,
          "name": "dyasc-2019",
          "slug": "Jorocha/dyasc-2019"
        },
        "branch": {
          "@type": "branch",
          "@href": "/repo/26882066/branch/master",
          "@representation": "minimal",
          "name": "master"
        },
        "tag": null,
        "commit": {
          "@type": "commit",
          "@representation": "minimal",
          "id": 187785603,
          "sha": "a33d81af3640fd1119acd1cc49be29c2254df2f7",
          "ref": "refs/heads/master",
          "message": "Agrega README",
          "compare_url": "https://github.com/Jorocha/dyasc-2019/compare/2d41f5a689e4...a33d81af3640",
          "committed_at": null
        },
        "jobs": [
          {
            "@type": "job",
            "@href": "/job/617982919",
            "@representation": "minimal",
            "id": 617982919
          }
        ],
        "stages": [
  
        ],
        "created_by": {
          "@type": "user",
          "@href": "/user/1910772",
          "@representation": "minimal",
          "id": 1910772,
          "login": "Jorocha"
        },
        "updated_at": "2019-11-28T00:56:54.612Z"
      }
    ]
  })rawliteral";

String jsonStarted = R"rawliteral(
    {
    "@type": "builds",
    "@href": "/repo/26882066/builds?limit=1",
    "@representation": "standard",
    "@pagination": {
      "limit": 1,
      "offset": 0,
      "count": 22,
      "is_first": true,
      "is_last": false,
      "next": {
        "@href": "/repo/26882066/builds?limit=1&offset=1",
        "offset": 1,
        "limit": 1
      },
      "prev": null,
      "first": {
        "@href": "/repo/26882066/builds?limit=1",
        "offset": 0,
        "limit": 1
      },
      "last": {
        "@href": "/repo/26882066/builds?limit=1&offset=21",
        "offset": 21,
        "limit": 1
      }
    },
    "builds": [
      {
        "@type": "build",
        "@href": "/build/617982918",
        "@representation": "standard",
        "@permissions": {
          "read": true,
          "cancel": true,
          "restart": true
        },
        "id": 617982918,
        "number": "22",
        "state": "started",
        "duration": 41,
        "event_type": "push",
        "previous_state": "failed",
        "pull_request_title": null,
        "pull_request_number": null,
        "started_at": "2019-11-28T00:56:13Z",
        "finished_at": "2019-11-28T00:56:54Z",
        "private": false,
        "repository": {
          "@type": "repository",
          "@href": "/repo/26882066",
          "@representation": "minimal",
          "id": 26882066,
          "name": "dyasc-2019",
          "slug": "Jorocha/dyasc-2019"
        },
        "branch": {
          "@type": "branch",
          "@href": "/repo/26882066/branch/master",
          "@representation": "minimal",
          "name": "master"
        },
        "tag": null,
        "commit": {
          "@type": "commit",
          "@representation": "minimal",
          "id": 187785603,
          "sha": "a33d81af3640fd1119acd1cc49be29c2254df2f7",
          "ref": "refs/heads/master",
          "message": "Agrega README",
          "compare_url": "https://github.com/Jorocha/dyasc-2019/compare/2d41f5a689e4...a33d81af3640",
          "committed_at": null
        },
        "jobs": [
          {
            "@type": "job",
            "@href": "/job/617982919",
            "@representation": "minimal",
            "id": 617982919
          }
        ],
        "stages": [
  
        ],
        "created_by": {
          "@type": "user",
          "@href": "/user/1910772",
          "@representation": "minimal",
          "id": 1910772,
          "login": "Jorocha"
        },
        "updated_at": "2019-11-28T00:56:54.612Z"
      }
    ]
  })rawliteral";

// Test passed build. Req 1 y 2
void testBuildPassedTurnsOnGreenLed(void) {
  StaticJsonBuffer <4000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(jsonPassed);
  String status = root["builds"][0]["state"]; 
  if(status.equals("passed")){
    balizaTest.passedBuild();
  }
  TEST_ASSERT_EQUAL(HIGH, digitalRead(greenLedTest));
}

// Test failed build. Req 1 y 2
void testBuildFailedTurnsOnRedLed(void) {
  StaticJsonBuffer <4000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(jsonFailed);
  String status = root["builds"][0]["state"]; 
  if(status.equals("failed")){
    balizaTest.failedBuild();
  }
  TEST_ASSERT_EQUAL(HIGH, digitalRead(redLedTest));
}


void testHttpErrorTurnsOnYellowLed(void) {
  String stringHttpCode = "4XX";
  if(stringHttpCode.equals("4XX")){
    balizaTest.httpConnectionError();
  }
  TEST_ASSERT_EQUAL(HIGH, digitalRead(yellowLedTest));
}

// Test WiFi disconnected. Req 5
void testWiFiDisconnectedTurnsOnOrangeLed(void) {
  if (WiFi.status() != WL_CONNECTED){
    balizaTest.wifiDisconnected();
  }
  TEST_ASSERT_EQUAL(HIGH, digitalRead(orangeLedTest));
}

// Test change state. Req 3
void testChangeStateBlinksGreenLed(void) {
  StaticJsonBuffer <4000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(jsonStarted);
  String status = root["builds"][0]["state"]; 
  if(status.equals("started")){
    balizaTest.startedBuild();
  }
  // TEST_ASSERT_EQUAL(HIGH, digitalRead(redLedTest));
}

// Test WiFi connection. Req 4
void testWiFiConnection(void) {
}

void setup() {
    // NOTE!!! Wait for > 2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    UNITY_BEGIN();    // IMPORTANT LINE!
}

uint8_t i = 0;
uint8_t max_blinks = 3;

void loop() {
    if (i < max_blinks)
    {
      RUN_TEST(testBuildPassedTurnsOnGreenLed);
      delay(10000);
      RUN_TEST(testBuildFailedTurnsOnRedLed);
      delay(10000);
      RUN_TEST(testHttpErrorTurnsOnYellowLed);
      delay(10000);
      RUN_TEST(testWiFiDisconnectedTurnsOnOrangeLed);
      delay(10000);
      RUN_TEST(testChangeStateBlinksGreenLed);
      delay(10000);
      RUN_TEST(testWiFiConnection);
      delay(10000);
      i++;
    }
    else if (i == max_blinks) {
      UNITY_END(); // stop unit testing
    }
}