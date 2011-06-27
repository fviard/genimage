/*
 * Copyright (c) 2011 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define _GNU_SOURCE
#include <confuse.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "genimage.h"

static int jffs2_generate(struct image *image)
{
	int ret;
	char *extraargs;

	if (!image->flash_type) {
		printf("no flash type given for %s\n", image->file);
		return -EINVAL;
	}

	extraargs = cfg_getstr(image->imagesec, "extraargs");

	ret = systemp(image, "%s --eraseblock=%d -d %s -o %s %s",
			get_opt("mkfsjffs2"),
			image->flash_type->pebsize, mountpath(image), imageoutfile(image),
			extraargs);

	return ret;
}

static int jffs2_setup(struct image *image, cfg_t *cfg)
{
	return 0;
}

static cfg_opt_t jffs2_opts[] = {
	CFG_STR("extraargs", "", CFGF_NONE),
	CFG_END()
};

struct image_handler jffs2_handler = {
	.type = "jffs2",
	.generate = jffs2_generate,
	.setup = jffs2_setup,
	.opts = jffs2_opts,
};
