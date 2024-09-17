#ifndef ELOADSTORE_H
#define ELOADSTORE_H

#include <arch.h>

#define _LDRH( rd0, rs1, rs2 ) _LDH( rd0, rs1 ); rs1 = rs1 - rs2
#define _LDRH_U( rd0, rs1, rs2 ) _LDH( rd0, rs1 ); rs1 = rs1 + rs2
#define _LDRH_P( rd0, rs1, rs2 ) _LDH( rd0, rs1 - rs2 )
#define _LDRH_UP( rd0, rs1, rs2 ) _LDH( rd0, rs1 + rs2 )
#define _LDRH_WP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _LDH( rd0, rs1 )
#define _LDRH_WUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _LDH( rd0, rs1 )

#define _LDRSB( rd0, rs1, rs2 ) _LDBS( rd0, rs1 ); rs1 = rs1 - rs2
#define _LDRSB_U( rd0, rs1, rs2 ) _LDBS( rd0, rs1 ); rs1 = rs1 + rs2
#define _LDRSB_P( rd0, rs1, rs2 ) _LDBS( rd0, rs1 - rs2 )
#define _LDRSB_UP( rd0, rs1, rs2 ) _LDBS( rd0, rs1 + rs2 )
#define _LDRSB_WP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _LDBS( rd0, rs1 )
#define _LDRSB_WUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _LDBS( rd0, rs1 )

#define _LDRSH( rd0, rs1, rs2 ) _LDHS( rd0, rs1 ); rs1 = rs1 - rs2
#define _LDRSH_U( rd0, rs1, rs2 ) _LDHS( rd0, rs1 ); rs1 = rs1 + rs2
#define _LDRSH_P( rd0, rs1, rs2 ) _LDHS( rd0, rs1 - rs2 )
#define _LDRSH_UP( rd0, rs1, rs2 ) _LDHS( rd0, rs1 + rs2 )
#define _LDRSH_WP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _LDHS( rd0, rs1 )
#define _LDRSH_WUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _LDHS( rd0, rs1 )

#define _LDRD( rd0, rd1, rs1, rs2 ) _LD(rd0, rs1); _LD(rd1, rs1 + 4); rs1 = rs1 - rs2
#define _LDRD_U( rd0, rd1, rs1, rs2 ) _LD(rd0, rs1); _LD(rd1, rs1 + 4); rs1 = rs1 + rs2
#define _LDRD_P( rd0, rd1, rs1, rs2 ) _LD(rd0, rs1 - rs2); _LD(rd1, rs1 - rs2 + 4)
#define _LDRD_UP( rd0, rd1, rs1, rs2 ) _LD(rd0, rs1 + rs2); _LD(rd1, rs1 + rs2 + 4)
#define _LDRD_WP( rd0, rd1, rs1, rs2 ) rs1 = rs1 - rs2; _LD(rd0, rs1); _LD(rd1, rs1 + 4)
#define _LDRD_WUP( rd0, rd1, rs1, rs2 ) rs1 = rs1 + rs2; _LD(rd0, rs1); _LD(rd1, rs1 + 4)

#define _STRH( rd0, rs1, rs2 ) _STH( rs1, rd0 ); rs1 = rs1 - rs2
#define _STRH_U( rd0, rs1, rs2 ) _STH( rs1, rd0 ); rs1 = rs1 + rs2
#define _STRH_P( rd0, rs1, rs2 ) _STH( rs1 - rs2, rd0 )
#define _STRH_UP( rd0, rs1, rs2 ) _STH( rs1 + rs2, rd0 )
#define _STRH_WP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _STH( rs1, rd0 )
#define _STRH_WUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _STH( rs1, rd0 )

#define _STRD( rd0, rd1, rs1, rs2 ) _ST(rs1, rd0); _ST(rs1 + 4, rd1); rs1 = rs1 - rs2
#define _STRD_U( rd0, rd1, rs1, rs2 ) _ST(rs1, rd0); _ST(rs1 + 4, rd1); rs1 = rs1 + rs2
#define _STRD_P( rd0, rd1, rs1, rs2 ) _ST(rs1 - rs2, rd0); _ST(rs1 - rs2 + 4, rd1)
#define _STRD_UP( rd0, rd1, rs1, rs2 ) _ST(rs1 + rs2, rd0); _ST(rs1 + rs2 + 4, rd1)
#define _STRD_WP( rd0, rd1, rs1, rs2 ) rs1 = rs1 - rs2; _ST(rs1, rd0); _ST(rs1 + 4, rd1)
#define _STRD_WUP( rd0, rd1, rs1, rs2 ) rs1 = rs1 + rs2; _ST(rs1, rd0); _ST(rs1 + 4, rd1)

namespace arm2x {
	_INSTRUCTION( _strh )
		_STRH( _RD, _RN, _RM );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrh )
		_LDRH( _RD, _RN, _RM );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _strh_u )
		_STRH_U( _RD, _RN, _RM );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrh_u )
		_LDRH_U( _RD, _RN, _RM );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _strh_p )
		_STRH_P( _RD, _RN, _RM );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrh_p )
		_LDRH_P( _RD, _RN, _RM );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _strh_wp )
		_STRH_WP( _RD, _RN, _RM );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrh_wp )
		_LDRH_WP( _RD, _RN, _RM );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _strh_up )
		_STRH_UP( _RD, _RN, _RM );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrh_up )
		_LDRH_UP( _RD, _RN, _RM );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _strh_wup )
		_STRH_WUP( _RD, _RN, _RM );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrh_wup )
		_LDRH_WUP( _RD, _RN, _RM );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _strh_i )
		_LDI( _RT, _DISP );
		_STRH( _RD, _RN, _RT );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _DISP );
	_END

	_INSTRUCTION( _ldrh_i )
		_LDI( _RT, _DISP );
		_LDRH( _RD, _RN, _RT );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _DISP );
	_END

	_INSTRUCTION( _strh_iu )
		_LDI( _RT, _DISP );
		_STRH_U( _RD, _RN, _RT );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _DISP );
	_END

	_INSTRUCTION( _ldrh_iu )
		_LDI( _RT, _DISP );
		_LDRH_U( _RD, _RN, _RT );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _DISP );
	_END

	_INSTRUCTION( _strh_ip )
		_LDI( _RT, _DISP );
		_STRH_P( _RD, _RN, _RT );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrh_ip )
		_LDI( _RT, _DISP );
		_LDRH_P( _RD, _RN, _RT );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]" );
	_END

	_INSTRUCTION( _strh_wip )
		_LDI( _RT, _DISP );
		_STRH_WP( _RD, _RN, _RT );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrh_wip )
		_LDI( _RT, _DISP );
		_LDRH_WP( _RD, _RN, _RT );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]!" );
	_END

	_INSTRUCTION( _strh_iup )
		_LDI( _RT, _DISP );
		_STRH_UP( _RD, _RN, _RT );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrh_iup )
		_LDI( _RT, _DISP );
		_LDRH_UP( _RD, _RN, _RT );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]" );
	_END

	_INSTRUCTION( _strh_wiup )
		_LDI( _RT, _DISP );
		_STRH_WUP( _RD, _RN, _RT );
		_LOG( "strh r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrh_wiup )
		_LDI( _RT, _DISP );
		_LDRH_WUP( _RD, _RN, _RT );
		_LOG( "ldrh r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrsb )
		_LDRSB( _RD, _RN, _RM );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrsb_u )
		_LDRSB_U( _RD, _RN, _RM );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrsb_p )
		_LDRSB_P( _RD, _RN, _RM );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrsb_wp )
		_LDRSB_WP( _RD, _RN, _RM );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrsb_up )
		_LDRSB_UP( _RD, _RN, _RM );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrsb_wup )
		_LDRSB_WUP( _RD, _RN, _RM );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrsb_i )
		_LDI( _RT, _DISP );
		_LDRSB( _RD, _RN, _RT );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _DISP );
	_END

	_INSTRUCTION( _ldrsb_iu )
		_LDI( _RT, _DISP );
		_LDRSB_U( _RD, _RN, _RT );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _DISP );
	_END

	_INSTRUCTION( _ldrsb_ip )
		_LDI( _RT, _DISP );
		_LDRSB_P( _RD, _RN, _RT );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrsb_wip )
		_LDI( _RT, _DISP );
		_LDRSB_WP( _RD, _RN, _RT );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrsb_iup )
		_LDI( _RT, _DISP );
		_LDRSB_UP( _RD, _RN, _RT );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrsb_wiup )
		_LDI( _RT, _DISP );
		_LDRSB_WUP( _RD, _RN, _RT );
		_LOG( "ldrsb r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrsh )
		_LDRSH( _RD, _RN, _RM );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrsh_u )
		_LDRSH_U( _RD, _RN, _RM );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrsh_p )
		_LDRSH_P( _RD, _RN, _RM );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrsh_wp )
		_LDRSH_WP( _RD, _RN, _RM );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrsh_up )
		_LDRSH_UP( _RD, _RN, _RM );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrsh_wup )
		_LDRSH_WUP( _RD, _RN, _RM );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrsh_i )
		_LDI( _RT, _DISP );
		_LDRSH( _RD, _RN, _RT );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _DISP );
	_END

	_INSTRUCTION( _ldrsh_iu )
		_LDI( _RT, _DISP );
		_LDRSH_U( _RD, _RN, _RT );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _DISP );
	_END

	_INSTRUCTION( _ldrsh_ip )
		_LDI( _RT, _DISP );
		_LDRSH_P( _RD, _RN, _RT );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrsh_wip )
		_LDI( _RT, _DISP );
		_LDRSH_WP( _RD, _RN, _RT );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrsh_iup )
		_LDI( _RT, _DISP );
		_LDRSH_UP( _RD, _RN, _RT );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrsh_wiup )
		_LDI( _RT, _DISP );
		_LDRSH_WUP( _RD, _RN, _RT );
		_LOG( "ldrsh r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]!" );
	_END

	_INSTRUCTION( _strd )
		_STRD( _RD, _RH, _RN, _RM );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrd )
		_LDRD( _RD, _RH, _RN, _RM );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _strd_u )
		_STRD_U( _RD, _RH, _RN, _RM );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldrd_u )
		_LDRD_U( _RD, _RH, _RN, _RM );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _strd_p )
		_STRD_P( _RD, _RH, _RN, _RM );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrd_p )
		_LDRD_P( _RD, _RH, _RN, _RM );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _strd_wp )
		_STRD_WP( _RD, _RH, _RN, _RM );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrd_wp )
		_LDRD_WP( _RD, _RH, _RN, _RM );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _strd_up )
		_STRD_UP( _RD, _RH, _RN, _RM );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldrd_up )
		_LDRD_UP( _RD, _RH, _RN, _RM );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _strd_wup )
		_STRD_WUP( _RD, _RH, _RN, _RM );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldrd_wup )
		_LDRD_WUP( _RD, _RH, _RN, _RM );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _strd_i )
		_LDI( _RT, _DISP );
		_STRD( _RD, _RH, _RN, _RT );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _DISP );
	_END

	_INSTRUCTION( _ldrd_i )
		_LDI( _RT, _DISP );
		_LDRD( _RD, _RH, _RN, _RT );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _DISP );
	_END

	_INSTRUCTION( _strd_iu )
		_LDI( _RT, _DISP );
		_STRD_U( _RD, _RH, _RN, _RT );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _DISP );
	_END

	_INSTRUCTION( _ldrd_iu )
		_LDI( _RT, _DISP );
		_LDRD_U( _RD, _RH, _RN, _RT );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _DISP );
	_END

	_INSTRUCTION( _strd_ip )
		_LDI( _RT, _DISP );
		_STRD_P( _RD, _RH, _RN, _RT );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrd_ip )
		_LDI( _RT, _DISP );
		_LDRD_P( _RD, _RH, _RN, _RT );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]" );
	_END

	_INSTRUCTION( _strd_wip )
		_LDI( _RT, _DISP );
		_STRD_WP( _RD, _RH, _RN, _RT );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrd_wip )
		_LDI( _RT, _DISP );
		_LDRD_WP( _RD, _RH, _RN, _RT );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _DISP << "]!" );
	_END

	_INSTRUCTION( _strd_iup )
		_LDI( _RT, _DISP );
		_STRD_UP( _RD, _RH, _RN, _RT );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]" );
	_END

	_INSTRUCTION( _ldrd_iup )
		_LDI( _RT, _DISP );
		_LDRD_UP( _RD, _RH, _RN, _RT );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]" );
	_END

	_INSTRUCTION( _strd_wiup )
		_LDI( _RT, _DISP );
		_STRD_WUP( _RD, _RH, _RN, _RT );
		_LOG( "strd r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]!" );
	_END

	_INSTRUCTION( _ldrd_wiup )
		_LDI( _RT, _DISP );
		_LDRD_WUP( _RD, _RH, _RN, _RT );
		_LOG( "ldrd r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _DISP << "]!" );
	_END
};

#endif
