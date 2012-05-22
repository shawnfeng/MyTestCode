#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <zookeeper.h>

#include "service.h"


void watcher(zhandle_t *zzh, int type, int state, const char *path,
             void *watcherCtx)
{
	printf("@@@@::watcher call\rn");
}

const char *zoo_clusters = "localhost:4180,localhost:4181,localhost:4182";

int main()
{
	char buffer[512];
	zhandle_t *zh;
	zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);
	zh = zookeeper_init(zoo_clusters, watcher, 10000, 0, 0, 0);

	int rc = zoo_create(zh,"/abc","", 0, &ZOO_OPEN_ACL_UNSAFE, 0,
			    buffer, sizeof(buffer)-1);
	printf("@@@@rc=%d\n", rc);

	const char *data = "oh my lady gaga!";
	rc = zoo_create(zh,"/abc/xyz", data, strlen(data), &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL | ZOO_SEQUENCE,
			    buffer, sizeof(buffer)-1);
	printf("@@@@rc=%d\n", rc);
	sleep(1000);

	return 0;

}
