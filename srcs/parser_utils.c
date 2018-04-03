/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:44:40 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 16:16:24 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t		ft_getnumvar(size_t num_var_shape, t_list *form)
{
	if (FORM(form)->mat.text_m == 0)
		return (num_var_shape + NVARMAT);
	else if (FORM(form)->mat.text_m == M_TEX)
		return (num_var_shape + NVARMAT + NVARTEX);
	else if (FORM(form)->mat.text_m == M_GEN)
		return (num_var_shape + NVARMAT + NVARGEN);
	return (ERROR);
}

t_bool		ft_checkshapevalues(t_setup *setup, t_shape shape)
{
	if ((shape.type == MOE) && shape.mat.text_m)
		return (setup->error = TEX_MT_ERROR);
	//if (shape.mat.text_m == M_TEX && shape.mat.text_c.text_num >= NUM_TEXT)
	
	return (TRUE);
}

t_bool		*ft_text_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "texture_num") == 0)
		flag[n_flag] = ft_getsize_tfromenv(&FORM(form)->mat.text_c.text_num,
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "size_x") == 0)
		flag[n_flag + 1] = ft_getdoublefromenv(&FORM(form)->mat.text_c.size_x,
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "size_y") == 0)
		flag[n_flag + 2] = ft_getdoublefromenv(&FORM(form)->mat.text_c.size_y,
				ENVSTRUCT(env)->value);
	return (flag);
}

t_bool		*ft_gen_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "mode") == 0)
		flag[n_flag] = ft_getsize_tfromenv(&FORM(form)->mat.gen.mode,
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "p_color") == 0)
		flag[n_flag + 1] = ft_getcolfromenv(&FORM(form)->mat.gen.col, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "perlin_layers") == 0)
		flag[n_flag + 2] = ft_getsize_tfromenv(\
			&FORM(form)->mat.gen.p_layers, ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "perlin_frequency") == 0)
		flag[n_flag + 3] = ft_getdoublefromenv(&FORM(form)->mat.gen.p_f,
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "perlin_persistance") == 0)
		flag[n_flag + 4] = ft_getdoublefromenv(&FORM(form)->mat.gen.p_prst,
				ENVSTRUCT(env)->value);
	return (flag);
}

t_bool		*ft_mat_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[n_flag] = ft_getcolfromenv(&FORM(form)->mat.col, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "reflexion") == 0)
		flag[n_flag + 1] = ft_getdoublefromenv(&FORM(form)->mat.refl, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "refractive_index") == 0)
		flag[n_flag + 2] = ft_getdoublefromenv(&FORM(form)->mat.n, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "transparency") == 0)
		flag[n_flag + 3] = ft_getdoublefromenv(&FORM(form)->mat.trsp, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "specularity") == 0)
		flag[n_flag + 4] = ft_getdoublefromenv(&FORM(form)->mat.s, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "texture_mode") == 0)
		flag[n_flag + 5] = ft_getsize_tfromenv(&FORM(form)->mat.text_m, \
				ENVSTRUCT(env)->value);
	else if (FORM(form)->mat.text_m)
		flag = ((FORM(form)->mat.text_m == M_TEX) ? \
				ft_text_struct_pop(form, env, flag, n_flag + 6) : \
				ft_gen_struct_pop(form, env, flag, n_flag + 6));
	return (flag);
}
