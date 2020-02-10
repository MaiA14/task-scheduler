/******************************************************************************
 * @Author Mai Aloni 
 * @Version 20-08-2019
 * Reviewer: Hay Hoffman
 * Title: UID	
 * Description: This file contains functions of UID, 
   such as: create UID and UIDIsSame.
 *
 * compile: gd -I include/  tests/test_UID.c UID.c
 ******************************************************************************/

#include <assert.h> /*assert*/
#include <time.h>  /*time*/
#include <unistd.h> /*getpid*/

#include "UID.h" /*UID functions declartions */

const ilrd_uid_t BAD_UID = {0,0,-1};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t ilrd_uid = {0, 0, 0};
	static size_t counter = 0;
	
	ilrd_uid.counter = counter;
	ilrd_uid.time = time(NULL); 
	ilrd_uid.pid = getpid();
	
	if (-1 == ilrd_uid.time)
	{
		return BAD_UID;
	}
	++counter;
				
	return ilrd_uid;
}


int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	
	if (uid1.counter == uid2.counter &&
	    uid1.time == uid2.time &&
	    uid1.pid == uid2.pid)
 	{
 		return 1;
 	}
 	
 	return 0; 
}

  


