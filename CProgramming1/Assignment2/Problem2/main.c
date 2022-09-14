#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

/*
 * 본 과제 프로그램은 libcurl(https://curl.haxx.se/libcurl/) 외부 라이브러리를 사용하며
 * Debian Linux(Ubuntu 18.04 LTS)에서 테스트되었습니다.
 * apt-get install libcurl4-openssl-dev
 * gcc main.c -lcurl -o main
 * ./main
 */

struct URLData {
    size_t size;
    char *data;
};

/**
 * libcurl의 callback 함수를 정의한다.
 * https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
 */
size_t write_callback(void *ptr, size_t size, size_t nmemb, struct URLData *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char *tmp;
    data->size += (size * nmemb);
    tmp = realloc(data->data, data->size + 1);
    if (tmp) {
        data->data = tmp;
    }
    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';
    return size * nmemb;
}

/**
 * 매개변수의 URL에 Http Get 요청시 응답하는 값을 가져온다.
 * @param url Http Get 요청할 URL
 * @return 응답된 body String
 */
char *requestURL(char *url) {
    CURL *curl;
    struct URLData data;
    data.size = 0;
    data.data = malloc(4096);
    data.data[0] = '\0';
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    return data.data;
}

const char *API_URL = "https://api.exchangeratesapi.io/latest?symbols=KRW&base=USD";
const char *START_STRING = "{\"KRW\":";
const char *END_STRING = "}";

/**
 * 유럽 중앙은행이 제공하는 USD-KRW 환율 정보를 API를 통해 가져온다.
 * https://exchangeratesapi.io/
 * @param json API에서 반환된 JSON String
 * @return 1USD에 해당하는 KRW의 가치
 */
double extractKRWExchangeRateFromJSON(char *json) {
    char krwStr;
    char *startPart = strstr(json, START_STRING) + strlen(START_STRING);
    char *endPart = strstr(startPart, END_STRING);
    int length = endPart - startPart;
    char krwPart[length];
    strncpy(krwPart, startPart, length);

    return atof(krwPart);
}

double getUSD2KRWExchangeRate() {
    char *data = requestURL(API_URL);
    if (data) {
        double rate = extractKRWExchangeRateFromJSON(data);
        free(data);
        return rate;
    }
}

const float ASSIGNMENT_EXCHANGE_RATE = 1234.5;

/**
 * 2. 달러($)를 입력하면 원(\) 으로 얼마인지 알려주는 프로그램을 작성하라. 환율은 1$ 당 1234.5\ 이라고 가정한다. 모든 변수는 float형으로 입력한다.
 */
void runAssignment2() {
    float dollar;
    double rate = getUSD2KRWExchangeRate();
    printf("달러를 입력 하세요:");
    scanf("%f", &dollar);
    printf("%f원 입니다.", dollar * ASSIGNMENT_EXCHANGE_RATE);
    printf("\n");
    printf("※현 시각 실제 환율로 계산하면 %.1lf원입니다. (1USD:%.1lfKRW, 유럽 중앙은행)", dollar * rate, rate);
    printf("\n");
}

int main() {
    runAssignment2();
}
