#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "linked_list.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

typedef struct
{
    const char *description;
    int (*function)(void);
} test_case_t;

static uint32_t total_tests  = 0U;
static uint32_t passed_tests = 0U;

static void report_test(uint32_t current_test,
                        uint32_t planned_tests,
                        const char *description,
                        int result)
{
    ++total_tests;

    if (TEST_PASS == result)
    {
        ++passed_tests;
    }

    (void)printf("[%02u/%02u] %-30s [%s]\n",
                 current_test,
                 planned_tests,
                 description,
                 (TEST_PASS == result) ? "PASS" : "FAIL");

    (void)fflush(stdout);
}

static int test_init(void)
{
    list_node_t *head = NULL;

    if (LIST_STATUS_SUCCESS != linked_list_init(&head))
    {
        return TEST_FAIL;
    }

    if (NULL != head)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_push_back_empty_list(void)
{
    list_node_t *head = NULL;

    if (LIST_STATUS_SUCCESS != linked_list_push_back(&head, 10U))
    {
        return TEST_FAIL;
    }

    if ((NULL == head) ||
        (10U != head->data) ||
        (NULL != head->next))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_push_back_multiple_nodes(void)
{
    list_node_t *head = NULL;
    list_node_t *current = NULL;

    if ((LIST_STATUS_SUCCESS != linked_list_push_back(&head, 10U)) ||
        (LIST_STATUS_SUCCESS != linked_list_push_back(&head, 20U)) ||
        (LIST_STATUS_SUCCESS != linked_list_push_back(&head, 30U)))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    current = head;

    if ((NULL == current) || (10U != current->data))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    current = current->next;

    if ((NULL == current) || (20U != current->data))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    current = current->next;

    if ((NULL == current) || (30U != current->data))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    if (NULL != current->next)
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_find_existing_value(void)
{
    list_node_t *head = NULL;
    list_node_t *found_node = NULL;

    (void)linked_list_push_back(&head, 10U);
    (void)linked_list_push_back(&head, 20U);
    (void)linked_list_push_back(&head, 30U);

    if (LIST_STATUS_SUCCESS !=
        linked_list_find(head, 20U, &found_node))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    if ((NULL == found_node) || (20U != found_node->data))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_find_missing_value(void)
{
    list_node_t *head = NULL;
    list_node_t *found_node = NULL;

    (void)linked_list_push_back(&head, 10U);
    (void)linked_list_push_back(&head, 20U);

    if (LIST_STATUS_NOT_FOUND !=
        linked_list_find(head, 99U, &found_node))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    if (NULL != found_node)
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_remove_head(void)
{
    list_node_t *head = NULL;

    (void)linked_list_push_back(&head, 10U);
    (void)linked_list_push_back(&head, 20U);

    if (LIST_STATUS_SUCCESS != linked_list_remove(&head, 10U))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    if ((NULL == head) || (20U != head->data))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_remove_middle(void)
{
    list_node_t *head = NULL;

    (void)linked_list_push_back(&head, 10U);
    (void)linked_list_push_back(&head, 20U);
    (void)linked_list_push_back(&head, 30U);

    if (LIST_STATUS_SUCCESS != linked_list_remove(&head, 20U))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    if ((NULL == head) ||
        (10U != head->data) ||
        (NULL == head->next) ||
        (30U != head->next->data) ||
        (NULL != head->next->next))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_remove_missing_value(void)
{
    list_node_t *head = NULL;

    (void)linked_list_push_back(&head, 10U);
    (void)linked_list_push_back(&head, 20U);

    if (LIST_STATUS_NOT_FOUND != linked_list_remove(&head, 99U))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static int test_clear(void)
{
    list_node_t *head = NULL;

    (void)linked_list_push_back(&head, 10U);
    (void)linked_list_push_back(&head, 20U);
    (void)linked_list_push_back(&head, 30U);

    if (LIST_STATUS_SUCCESS != linked_list_clear(&head))
    {
        return TEST_FAIL;
    }

    if (NULL != head)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_head(void)
{
    if (LIST_STATUS_INVALID_ARGUMENT != linked_list_init(NULL))
    {
        return TEST_FAIL;
    }

    if (LIST_STATUS_INVALID_ARGUMENT !=
        linked_list_push_back(NULL, 10U))
    {
        return TEST_FAIL;
    }

    if (LIST_STATUS_INVALID_ARGUMENT !=
        linked_list_remove(NULL, 10U))
    {
        return TEST_FAIL;
    }

    if (LIST_STATUS_INVALID_ARGUMENT !=
        linked_list_clear(NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_output_node(void)
{
    list_node_t *head = NULL;

    (void)linked_list_push_back(&head, 10U);

    if (LIST_STATUS_INVALID_ARGUMENT !=
        linked_list_find(head, 10U, NULL))
    {
        (void)linked_list_clear(&head);
        return TEST_FAIL;
    }

    (void)linked_list_clear(&head);

    return TEST_PASS;
}

static const test_case_t test_cases[] =
{
    { "Initialize empty list",       test_init },
    { "Push into empty list",        test_push_back_empty_list },
    { "Push multiple nodes",         test_push_back_multiple_nodes },
    { "Find existing value",         test_find_existing_value },
    { "Find missing value",          test_find_missing_value },
    { "Remove head node",            test_remove_head },
    { "Remove middle node",          test_remove_middle },
    { "Remove missing value",        test_remove_missing_value },
    { "Clear list",                  test_clear },
    { "Null head pointer",           test_null_head },
    { "Null output node",            test_null_output_node }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running linked_list unit tests\n");
    (void)printf("========================================\n");

    for (uint32_t i = 0U; i < planned_tests; ++i)
    {
        report_test(i + 1U,
                    planned_tests,
                    test_cases[i].description,
                    test_cases[i].function());
    }

    const uint32_t failed_tests = total_tests - passed_tests;

    (void)printf("----------------------------------------\n");
    (void)printf("Summary\n");
    (void)printf("----------------------------------------\n");

    (void)printf("Executed : %u/%u\n",
                 total_tests,
                 planned_tests);

    (void)printf("Passed   : %u/%u (%.0f%%)\n",
                 passed_tests,
                 planned_tests,
                 (100.0 * (double)passed_tests) / (double)planned_tests);

    (void)printf("Failed   : %u/%u (%.0f%%)\n",
                 failed_tests,
                 planned_tests,
                 (100.0 * (double)failed_tests) / (double)planned_tests);

    (void)printf("========================================\n");

    return (0U == failed_tests) ? EXIT_SUCCESS : EXIT_FAILURE;
}