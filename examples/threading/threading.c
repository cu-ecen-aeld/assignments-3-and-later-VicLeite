#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    int rc;
    struct thread_data* thread_param_args = (struct thread_data*) thread_param;

    usleep(thread_param_args->wait_to_obtain_ms*1000);
    rc = pthread_mutex_lock(thread_param_args->mutex);
    if(rc != 0)
    {
        ERROR_LOG("pthread_mutex_lock failed with error code %d", rc);
        thread_param_args->thread_complete_success = false;
        return thread_param_args;
    }
    
    usleep(thread_param_args->wait_to_release_ms*1000);
    rc = pthread_mutex_unlock(thread_param_args->mutex);
    if(rc != 0)
    {
        ERROR_LOG("pthread_mutex_lock failed with error code %d", rc);
        thread_param_args->thread_complete_success = false;
        return thread_param_args;
    }

    thread_param_args->thread_complete_success = true;

    return thread_param_args;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    int rc;
    pthread_t thread_id;
    struct thread_data* thread_data = malloc(sizeof(struct thread_data));
    if(thread_data == NULL)
    {
        ERROR_LOG("malloc failed");
        return false;
    }
    
    thread_data->mutex = mutex;
    thread_data->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_data->wait_to_release_ms = wait_to_release_ms;
    thread_data->thread_finished = false;

    rc = pthread_create(&thread_id, NULL, threadfunc, (void*)thread_data);
    if(rc != 0)
    {
        ERROR_LOG("pthread_create failed with error code %d", rc);
        free(thread_data);
        return false;
    }

    *thread = thread_id;
    
    return true;
}

