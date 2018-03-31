/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 16:23:02 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/31 11:13:43 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define FILE_ERROR_S	"error: file doesn't exist or don't have the rights"
# define ENG_ERROR_S	"error: engine is not in the correct format"
# define LIGHT_ERROR_S	"error: light struct is not in the correct format"
# define PLANE_ERROR_S	"error: plane struct is not in the correct format"
# define SPHERE_ERROR_S	"error: sphere struct is not in the correct format"
# define CONE_ERROR_S	"error: cone struct is not in the correct format"
# define CYL_ERROR_S	"error: cylindre struct is not in the correct format"
# define TOR_ERROR_S	"error: torus struct is not in the correct format"
# define MOE_ERROR_S	"error: moebius struct is not in the correct format"
# define CAM_ERROR_S	"error: cam struct is not in the correct format"
# define SCN_ERROR_S	"error: scene is not in the correct format"
# define OBJ_ERROR_S	"error: objects are not in the correct format"
# define DIM_ERROR_S	"error: dim is not in the correct format [100;4000]"
# define TEX_MT_ERROR_S	"error: texture not allowed for torus and moebius"
# define XML_ERROR_S	"error: one of the xml struct is not in the correct format"
# define MAT_ERROR_S	"error: one of the material is not in the correct format"
# define GEN_ERROR_S	"error: generative struct is not in the correct format"
# define TEX_ERROR_S	"error: texture struct is not in the correct format"

typedef enum			e_error
{
	FILE_ERROR = 0,
	ENG_ERROR,
	LIGHT_ERROR,
	CAM_ERROR,
	PLANE_ERROR,
	SPHERE_ERROR,
	CONE_ERROR,
	CYLINDRE_ERROR,
	TORUS_ERROR,
	MOEBIUS_ERROR,
	SCN_ERROR,
	OBJ_ERROR,
	DIM_ERROR,
	TEX_MT_ERROR,
	XML_ERROR,
	MAT_ERROR,
	GEN_ERROR,
	TEX_ERROR,
	MAX_ERROR
}						t_error;

#endif
