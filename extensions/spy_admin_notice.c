/*
 *  ircd-ratbox: A slightly useful ircd.
 *  spy_admin_notice.c: Sends a notice when someone uses ADMIN.
 *
 *  Copyright (C) 2002 by the past and present ircd coders, and others.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 */
#include <ircd/stdinc.h>
#include <ircd/modules.h>
#include <ircd/hook.h>
#include <ircd/client.h>
#include <ircd/ircd.h>
#include <ircd/send.h>

static const char spy_desc[] = "Sends a notice when someone uses ADMIN";

void show_admin(hook_data *);

mapi_hfn_list_av1 admin_hfnlist[] = {
	{"doing_admin", (hookfn) show_admin},
	{NULL, NULL}
};

DECLARE_MODULE_AV2(admin_spy, NULL, NULL, NULL, NULL, admin_hfnlist, NULL, NULL, spy_desc);

void
show_admin(hook_data *data)
{
	sendto_realops_snomask(SNO_SPY, L_ALL,
			     "admin requested by %s (%s@%s) [%s]",
			     data->client->name, data->client->username,
			     data->client->host, data->client->servptr->name);
}
