#include "data_handler.h"
#include "read_api_key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct response_data {
    char *memory;
    size_t size;
};

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct response_data *mem = (struct response_data *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0; 

    return realsize;
}


struct Data show_whole_data() {
    struct Data d1;
    d1.number = 10;

    CURL *curl;
    CURLcode res;
    struct response_data chunk;
    chunk.memory = NULL; 
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if(curl) {
        const char *api_key = get_API_key();
        if(api_key == NULL) {
            fprintf(stderr, "API key is NULL. Please check the API key.\n");
            return d1;
        }

        char url[512];
        snprintf(url, sizeof(url), "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?sol=1000&page=2&api_key=%s", api_key);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Response from NASA API:\n%s\n", chunk.memory);
        }

        curl_easy_cleanup(curl);
    } else {
        printf("Error occurred while initializing CURL.\n");
    }

    if (chunk.memory) {
        free(chunk.memory);
    }

    curl_global_cleanup();

    return d1;
}

