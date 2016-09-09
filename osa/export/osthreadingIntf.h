#ifndef OSTHREADINGINTF_H
#define OSTHREADINGINTF_H

#include <common/commontypes.h>

typedef struct OsThread OsThread_t;
typedef struct OsMutex OsMutex_t;
typedef struct OsCondition OsCondition_t;

typedef void * (*ThreadExecutor_t)(void *data);

  /*!
   * \brief Interface towards threading mechanisms
   *
   * The implementation of this interface follows the PTHREADS API.
   */
typedef struct
{
  /*!
   * \brief Creates a new thread
   *
   * The memory management of the data stays with the caller, it is not freed when calling thread_destroy.
   * All signal handling is disabled for the newly created thread.
   */
  Status_e (*thread_create)(OsThread_t ** t, ThreadExecutor_t exec, void *data);

  /*!
   * \brief Waits for the thread to terminate.
   */
  Status_e (*thread_join)(OsThread_t * t);
  
  /*!
   * \brief Causes  the  calling  thread to relinquish the CPU.
   *
   * The thread is placed at the end of the run queue for its
   * static priority and another thread is scheduled to run.
   */
  Status_e (*thread_yield)(void);

  /*!
   * \brief Joins and destroys a thread.
   */
  Status_e (*thread_destroy)(OsThread_t * t);

  /*!
   * \brief Creates a new mutex
   */
  Status_e (*mutex_create)(OsMutex_t **m);
  
  /*!
   * \brief Locks the mutex.
   *
   * If the mutex still exists and is locked, the call will block, until the mutex is acquired.
   * When the mutex is already destroyed, this function will return immediately, returning an ERROR.
   */
  Status_e (*mutex_lock)(OsMutex_t *m);
  
  /*!
   * \brief Tries to locks the mutex.
   *
   * Non blocking implementation of mutex_lock.
   */
  Status_e (*mutex_trylock)(OsMutex_t *m);
  
  /*!
   * \brief Unlocks the mutex.
   */
  Status_e (*mutex_unlock)(OsMutex_t *m);
  
  /*!
   * \brief Destroys the mutex
   */
  Status_e (*mutex_destroy)(OsMutex_t *m);

  /*!
   * \brief Creates a new condition
   */
  Status_e (*condition_create)(OsCondition_t ** c);

  /*!
   * \brief Signals a condition
   *
   * It is used to signal (or wake up) another thread which is waiting on the condition variable.
   * It should be called after mutex is locked, and must unlock mutex in order for condition_wait() routine to complete.
   */
  Status_e (*condition_signal)(OsCondition_t * c);

  /*!
   * \brief Waits for a condition to happen.
   *
   * Must be called with mutex locked by the calling thread.
   *
   * It releases the mutex and causes the calling thread to block on the condition variable.
   * Upon successful return, the mutex shall have been locked and shall be owned by the calling thread. 
   */
  Status_e (*condition_wait)(OsCondition_t * c, OsMutex_t * m);

  /*!
   * \brief Destroys the condition
   */
  Status_e (*condition_destroy)(OsCondition_t * c);
} OsThreadingIntf_t;

OsThreadingIntf_t *getOsThreadingIntf(void);

#ifdef UNITTESTS
void setDefaultOsThreadingIntfForUnittests(void);
void resetDefaultOsThreadingIntfForUnittests(void);
#endif

#endif
