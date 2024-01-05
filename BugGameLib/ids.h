/**
 * @file ids.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_IDS_H
#define PROJECT_1_BUGGAMELIB_IDS_H

/**
 * Menu id values
 */
enum IDs {
	/// Add Bug>Garbage Bug menu option
	IDM_BUGS_GARBAGE = wxID_HIGHEST + 1,

	/// Add Bug>Fat Garbage Bug menu option
	IDM_BUGS_GARBAGE_FAT,

	/// Add Bug>Null Bug menu option
	IDM_BUGS_NULL,

	/// Add Bug>Fat Null Bug menu option
	IDM_BUGS_NULL_FAT,

	/// Add Bug>Redundancy Fly menu option
	IDM_BUGS_REDUNDANCY,

	/// Add Bug>Fat Redundancy Fly menu option
	IDM_BUGS_REDUNDANCY_FAT,

	/// Add Bug>Feature menu option
	IDM_BUGS_FEATURE,

	/// Add Bug>Laptop menu option
	IDM_LAPTOP,

	/// Level IDs
	LEVEL_0, LEVEL_1, LEVEL_2, LEVEL_3,

	/// Determines if program shrinks
	SHRINK
};

#endif //PROJECT_1_BUGGAMELIB_IDS_H
