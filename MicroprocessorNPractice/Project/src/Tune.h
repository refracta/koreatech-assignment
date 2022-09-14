/*! \file */
#ifndef TUNE_H
#define TUNE_H

#define SUCCESS_TUNE(S) S.playTone('g', 5, 200);
#define FAIL_TUNE(S) S.playTone('F', 6, 100); S.playTone('F', 6, 100);

#endif