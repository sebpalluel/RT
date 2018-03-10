/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 18:47:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/01 17:11:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEFINE_H
# define LIBFT_DEFINE_H

# define MAX_INT					2147483647
# define MIN_INT					-2147483648
# define MAX_INT_DECIMAL			11
# define ABS(a)						((a) * (((a) > 0) * 2 - 1))
# define SQUARE(x)					((x) * (x))
# define MIN(a, b)					(((a) < (b)) ? (a) : (b))
# define MAX(a, b)					(((a) > (b)) ? (a) : (b))

# define BUFF_SIZE 					50
# define FD_MAX						256
# define READ_OK					1
# define READ_EOF					0
# define READ_ERR					-1

# define OK							0
# define ERROR						1
# define TRUE						1
# define FALSE						0

# define ESC						53
# define ENTER						36
# define LEFT						123
# define RIGHT						124
# define DOWN						125
# define UP							126
# define MINUS						27
# define EQUAL						24
# define DOT_KEY					47
# define SLASH_KEY					44
# define CTRL						256
# define STAR						67
# define SLASH						75
# define A_KEY						0
# define S_KEY						1
# define D_KEY						2
# define F_KEY						3
# define H_KEY						4
# define G_KEY						5
# define Z_KEY						6
# define X_KEY						7
# define C_KEY						8
# define V_KEY						9
# define B_KEY						11
# define Q_KEY						12
# define W_KEY						13
# define E_KEY						14
# define R_KEY						15
# define Y_KEY						16
# define T_KEY						17
# define O_KEY						31
# define U_KEY						32
# define I_KEY						34
# define P_KEY						35
# define L_KEY						37
# define J_KEY						38
# define K_KEY						40
# define N_KEY						45
# define M_KEY						46
# define ZERO						29
# define ONE						18
# define TWO						19
# define THREE						20
# define FOUR						21
# define FIVE						23
# define SIX						22
# define SEVEN						26
# define EIGHT						28
# define NINE						25

# define MOUSE_LEFT					1
# define MOUSE_RIGHT				2
# define MOUSE_SIDE					3
# define WHEEL_UP					4
# define WHEEL_DOWN					5

# define KEYPRESS					2
# define KEYRELEASE					3
# define BUTTONPRESS				4
# define BUTTONRELEASE				5
# define NOTIFY						6
# define EXPOSE						12
# define DESTROYNOTIFY				17

# define NOEVENTMASK				0L
# define KEYPRESSMASK				(1L<<0)
# define KEYRELEASEMASK				(1L<<1)
# define BUTTONPRESSMASK			(1L<<2)
# define BUTTONRELEASEMASK			(1L<<3)
# define ENTERWINDOWMASK			(1L<<4)
# define LEAVEWINDOWMASK			(1L<<5)
# define POINTERMOTIONMASK			(1L<<6)
# define POINTERMOTIONHINTMASK		(1L<<7)
# define BUTTON1MOTIONMASK			(1L<<8)
# define BUTTON2MOTIONMASK			(1L<<9)
# define BUTTON3MOTIONMASK			(1L<<10)
# define BUTTON4MOTIONMASK			(1L<<11)
# define BUTTON5MOTIONMASK			(1L<<12)
# define BUTTONMOTIONMASK			(1L<<13)
# define KEYMAPSTATEMASK			(1L<<14)
# define EXPOSUREMASK				(1L<<15)
# define VISIBILITYCHANGEMASK		(1L<<16)
# define STRUCTURENOTIFYMASK		(1L<<17)
# define RESIZEREDIRECTMASK			(1L<<18)
# define SUBSTRUCTURENOTIFYMASK		(1L<<19)
# define SUBSTRUCTUREREDIRECTMASK	(1L<<20)
# define FOCUSCHANGEMASK			(1L<<21)
# define PROPERTYCHANGEMASK			(1L<<22)
# define COLORMAPCHANGEMASK			(1L<<23)
# define OWNERGRABBUTTONMASK		(1L<<24)

# define ANSI_RED					"\x1b[31m"
# define ANSI_GREEN					"\x1b[32m"
# define ANSI_YELLOW				"\x1b[33m"
# define ANSI_BLUE					"\x1b[34m"
# define ANSI_MAGENTA				"\x1b[35m"
# define ANSI_CYAN					"\x1b[36m"
# define ANSI_WHITE					"\x1b[97m"
# define ANSI_LIGHT_GRAY			"\x1b[47m"
# define ANSI_DARK_GRAY				"\x1b[100m"
# define ANSI_LIGHT_RED				"\x1b[101m"
# define ANSI_LIGHT_GREEN			"\x1b[102m"
# define ANSI_LIGHT_YELLOW			"\x1b[103m"
# define ANSI_LIGHT_BLUE			"\x1b[104m"
# define ANSI_LIGHT_MAGENTA			"\x1b[105m"
# define ANSI_LIGHT_CYAN			"\x1b[106m"
# define ANSI_RESET					"\x1b[0m"

# define ANSI_BOLD					"\e[1m"
# define ANSI_UNDERLINED			"\e[4m"
# define ANSI_BLINK					"\e[5m"
# define ANSI_BLACK					"\e[30m"
# define ANSI_MATRIX				"\e[5;32m"

/*
** --- Text Format ---
*/

# define NRM						"\x1B[0m"
# define RED						"\x1B[31m"
# define GRN						"\x1B[32m"
# define YEL						"\x1B[33m"
# define BLU						"\x1B[34m"
# define MAG						"\x1B[35m"
# define CYN						"\x1B[36m"
# define WHT						"\x1B[97m"
# define LGR						"\x1B[37m"
# define DGR						"\x1B[90m"

/*
** --- Memblock error formats ---
*/

# define MB_ERR_HD					"Memblock error: "
# define MB_ERR_M_FAIL				MB_ERR_HD "malloc failed too many times, exiting"
# define MB_ERR_E_BIG				MB_ERR_HD "element bigger than block, exiting"

/*
** --- Attributes ---
*/

# define NORETURN __attribute__((noreturn)) void
# define PRINTF __attribute__((format(printf, 1, 2))) void
# define LFT_HEADER LGR "[" YEL "LFT" LGR "]"

/*
** --- Utils ---
*/

# define ERR_GET_FILE_CONTENT_MALLOC LFT_HEADER " cannot get file\n"
# define ERR_FILE_OPEN LFT_HEADER " Failed to open file: "
# define MALLOC_FAILURE LFT_HEADER " malloc() failed, not enough ressources\n"
# define ERROR_NAME_HEADER LFT_HEADER " error\n"

#endif
