#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "../include/api.h"
#include "../include/utils.h"
#include "../include/constants.h"

char* fetch_word_from_api()
{
  static char word[WORD_LENGTH + 1] = "";
  char date[11];
  get_todays_date(date, sizeof(date));

  char endpoint[256];
  snprintf(endpoint, sizeof(endpoint), "%s%s", API_BASE_URL, date);

  CURL* curl = curl_easy_init();
  if (!curl) return NULL;

  char response[1024] = "";
  struct curl_slist* headers = NULL;

  headers = curl_slist_append(headers, "x-rapidapi-host" API_HOST);
  headers = curl_slist_append(headers, "x-rapidapi-key: " API_KEY);

  curl_easy_setopt(curl, CURLOPT_URL, endpoint);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

  CURLcode res = curl_easy_perform(curl);
  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  if (res != CURLE_OK)
  {
    fprintf(stderr, "Curl request failed: %s\n", curl_easy_strerror(res));
    return NULL;
  }

  cJSON* json = cJSON_Parse(response);
  if (!json)
  {
    fprintf(stderr, "Failed to parse JSON response.\n");
    return NULL;
  }

  cJSON* word_item = cJSON_GetObjectItemCaseSensitive(json, "word");
  if (cJSON_IsString(word_item) && (word_item->valuestring != NULL))
  {
    strncpy(word, word_item->valuestring, WORD_LENGTH);
    word[WORD_LENGTH] = '\0';
  } else {
    fprintf(stderr, "Failed to extract JSON response\n");
  }

  cJSON_Delete(json);
  return (*word) ? word : NULL;
}
