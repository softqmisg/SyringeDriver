#include <user_punc.h>

uint32_t PunctualGetTime(void){
	return HAL_GetTick();
}
// Creates a timeout handle.
void PunctualTimeoutSet(tTimeout *to, tTime ms){
    to->period = ms;
    to->due = PunctualGetTime() + ms;
}

// Check timeout.
uint8_t PunctualTimeoutCheck(tTimeout *to){
    int32_t timeDiff;

    // Get signed time difference.
    timeDiff = to->due - PunctualGetTime();

    // Expiration check.
    if(timeDiff <= 0){
        // Increase due time.
        to->due = to->due + to->period;

        // Check the new due.
        timeDiff = to->due - PunctualGetTime();
        if(timeDiff <= 0){
            // If already expired, reset the timeout.
			to->due = PunctualGetTime() + to->period;
        }

        // Expired.
        return 1;
    }else{
        // Not expired.
        return 0;
    }
}

