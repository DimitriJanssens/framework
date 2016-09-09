#include <testframework/testframework.h>

#include <stdio.h>
#include <stdlib.h>

#include <valgrind/memcheck.h>

void suite_run(const char_t * const name, Suite *suite)
{
	if(suite != NULL)
	{
		SRunner * runner = srunner_create(suite);
		if(runner != NULL)
		{
			char_t filename[1024];

    		/*	Jenkins sets this environment variable when it runs, I deliberatly don't use the osutils interface,
     		*	to avoid all the tests to become dependent on osutils, which is against unit tests priciples.
     		*/
		    
		    const char_t* resultsdir = getenv(ENV_RESULTS_DIR);

		    if (resultsdir != NULL)
		    {
		    	snprintf(filename,1024,"%s/%s_testresults.xml",resultsdir,name);
		    }
		    else
		    {
		    	snprintf(filename,1024,"/tmp/%s_testresults.xml",name);
		    }

		    srunner_set_fork_status(runner, CK_FORK_GETENV);
		    srunner_set_xml(runner,filename);

			srunner_run_all(runner, CK_NORMAL);
			srunner_free(runner);
			runner = NULL;
		}
	}
}

static void localResetMemleaks(void);
static uint64_t localGetMemleaks(void);
static void localValgrindSetup(void);
static void localValgrindTeardown(void);

static uint64_t localLeakedUntilNow = 0;

static void localResetMemleaks(void)
{
    localLeakedUntilNow = localGetMemleaks();
}

static uint64_t localGetMemleaks(void)
{
    uint64_t leaked;
    uint64_t dubious;
    uint64_t reachable;
    uint64_t suppressed;

    VALGRIND_DO_LEAK_CHECK;
    VALGRIND_COUNT_LEAKS(leaked, dubious, reachable, suppressed);

    if (leaked < localLeakedUntilNow)
    {
        printf("VALGRIND STRANGE SITUATION, reset everything\n");
        localLeakedUntilNow = leaked;
        
        (void) dubious;
    	(void) reachable;
    	(void) suppressed;
    }

    return leaked;
}

static void localValgrindSetup(void)
{
    if (RUNNING_ON_VALGRIND)
    {
        printf("RUNNING VALGRIND SETUP\n");
        localResetMemleaks();
    }
}

static void localValgrindTeardown(void)
{
    if (RUNNING_ON_VALGRIND)
    {
        printf("RUNNING VALGRIND TEARDOWN.\n");
        uint64_t leaked = (localGetMemleaks() - localLeakedUntilNow);
        ck_assert_msg(leaked == 0,"There are %"PRIu64" bytes leaked in this test\n",leaked);
    }
}

void tcase_add_valgrind_fixtures(TCase *tc)
{
	tcase_add_checked_fixture(tc, localValgrindSetup, localValgrindTeardown);
}
