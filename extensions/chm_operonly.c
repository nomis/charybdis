#include <ircd/stdinc.h>
#include <ircd/modules.h>
#include <ircd/hook.h>
#include <ircd/client.h>
#include <ircd/ircd.h>
#include <ircd/send.h>
#include <ircd/s_conf.h>
#include <ircd/s_user.h>
#include <ircd/s_serv.h>
#include <ircd/numeric.h>
#include <ircd/chmode.h>

static const char chm_operonly_desc[] =
	"Adds channel mode +O which makes a channel operator-only";

static void h_can_join(hook_data_channel *);

mapi_hfn_list_av1 operonly_hfnlist[] = {
	{ "can_join", (hookfn) h_can_join },
	{ NULL, NULL }
};

static unsigned int mymode;

static int
_modinit(void)
{
	mymode = cflag_add('O', CHM_D, chm_staff);
	if (mymode == 0)
		return -1;

	return 0;
}


static void
_moddeinit(void)
{
	cflag_orphan('O');
}

DECLARE_MODULE_AV2(chm_operonly, _modinit, _moddeinit, NULL, NULL, operonly_hfnlist, NULL, NULL, chm_operonly_desc);

static void
h_can_join(hook_data_channel *data)
{
	struct Client *source_p = data->client;
	struct Channel *chptr = data->chptr;

	if((chptr->mode.mode & mymode) && !IsOper(source_p)) {
		sendto_one_numeric(source_p, 520, "%s :Cannot join channel (+O) - you are not an IRC operator", chptr->chname);
		data->approved = ERR_CUSTOM;
	}
}

