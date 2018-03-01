/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:45:17 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 17:39:39 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** =============================================================================
** 							Global defined
** =============================================================================
*/

# define VERSION		"2.0.0"
# define VERSION_NICK	"2"
# define NAME			"Raytracer v" VERSION
# define NICK			"Rtv" VERSION_NICK

/*
** =============================================================================
** 							Colors
** =============================================================================
*/

# define C_NRM			"\033[0m"

# define C_SUC			"\033[38;2;141;143;38m"
# define C_ERR			"\033[38;2;231;76;60m"
# define C_CODE			"\033[38;2;243;156;18m"
# define C_WRN			"\033[38;2;230;126;34m"
# define C_INF			"\033[38;2;243;156;18m"

# define C_RED			"\033[38;2;231;76;60m"
# define C_ORANGE		"\033[38;2;230;126;34m"
# define C_YELLOW		"\033[38;2;241;196;15m"
# define C_GREEN		"\033[38;2;46;204;113m"
# define C_TEAL			"\033[38;2;26;188;156m"
# define C_BLUE			"\033[38;2;52;152;219m"
# define C_PURPLE		"\033[38;2;155;89;182m"
# define C_PINK			"\033[38;2;236;64;122m"

# define C_WHITE		"\033[38;2;236;240;241m"
# define C_LGREY		"\033[38;2;189;195;199m"
# define C_MGREY		"\033[38;2;149;165;166m"
# define C_DGREY		"\033[38;2;127;140;141m"
# define C_BLACK		"\033[38;2;44;62;80m"

/*
** =============================================================================
** 							Debug messages
** =============================================================================
*/

# define HEADER			C_MGREY "[" C_GREEN C_NICK C_MGREY "] "
# define HD				HEADER

# define ERR_HEADER		HD " [" C_ERR "x" C_MGREY "] [" C_CODE code C_MGREY "] "
# define WRN_HEADER		HD " [" C_WRN "!" C_MGREY "] [" sev C_MGREY "] "
# define INF_HEADER		HD " [" C_INF "i" C_MGREY "] "

# define WRN_SEV_MINOR	C_YELLOW "Minor" C_NRM
# define WRN_SEV_MEDIUM	C_ORANGE "Unsafe" C_NRM
# define WRN_SEV_MAJOR	C_RED "Critical" C_NRM

# define STR_ERR(c, s)	ERR_HEADER(c) C_LGREY s "\n" C_NRM
# define STR_WRN(s, sv)	WRN_HEADER(sv) C_LGREY s "\n" C_NRM
# define STR_INF(s)		INF_HEADER C_LGREY s C_NRM "\n"

/*
** =============================================================================
*/

#endif
