//
//  while(mood==0) // sad mood
//  {
//    matrix.clear();
//    // When counting down to the next blink, show the eye in the fully-
//    // open state.  On the last few counts (during the blink), look up
//    // the corresponding bitmap index.
//    matrix.drawBitmap(0, 0,
//    sadBlinkImg[
//      (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
//    blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
//    0                                       // No, show bitmap 0
//    ], 8, 8, LED_ON);
//    // Decrement blink counter.  At end, set random time for next blink.
//    if(--blinkCountdown == 0) blinkCountdown = random(5, 180);
//
//    // Add a pupil (2x2 black square) atop the blinky eyeball bitmap.
//    // Periodically, the pupil moves to a new position...
//    if(--gazeCountdown <= gazeFrames) {
//      // Eyes are in motion - draw pupil at interim position
//      matrix.fillRect(
//      newX - (dX * gazeCountdown / gazeFrames),
//      newY - (dY * gazeCountdown / gazeFrames),
//      2, 2, LED_OFF);
//      if(gazeCountdown == 0) {    // Last frame?
//        eyeX = newX; 
//        eyeY = newY; 
//        do { // Pick random positions until one is within the eye circle
//          newX = random(0,7); 
//          newY = random(5,7);
//          dX   = newX-3;  
//          dY   = newY-3;
//        } 
//        while((dX * dX + dY * dY) >= 10);        // Thank you Pythagoras
//        dX            = newX - eyeX;             // Horizontal distance to move
//        dY            = newY - eyeY;             // Vertical distance to move
//        gazeFrames    = random(3, 15);           // Duration of eye movement
//        gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
//      }
//    }
//    else {
//      // Not in motion yet -- draw pupil at current static position
//      matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
//    }
//
//
//    // Refresh all of the matrices in one quick pass
//    matrix.writeDisplay();
//
//    if(millis()-checkMillis > random(10000,30000))
//    {
//      sadNoise();
//      checkMillis = millis();
//    }
//
//    tapMillis = millis();
//
//    while(millis()-tapMillis < 40)
//    {
//      checkTaps();
//    }  
//    songMillis = millis();
//  }
//
//  while(mood==1) // neutral mood
//  {
//    // Draw eyeball in current state of blinkyness (no pupil).
//    matrix.clear();
//    // When counting down to the next blink, show the eye in the fully-
//    // open state.  On the last few counts (during the blink), look up
//    // the corresponding bitmap index.
//    matrix.drawBitmap(0, 0,
//    blinkImg[
//      (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
//    blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
//    0                                       // No, show bitmap 0
//    ], 8, 8, LED_ON);
//    // Decrement blink counter.  At end, set random time for next blink.
//    if(--blinkCountdown == 0) blinkCountdown = random(5, 180);
//
//    // Add a pupil (2x2 black square) atop the blinky eyeball bitmap.
//    // Periodically, the pupil moves to a new position...
//    if(--gazeCountdown <= gazeFrames) {
//      // Eyes are in motion - draw pupil at interim position
//      matrix.fillRect(
//      newX - (dX * gazeCountdown / gazeFrames),
//      newY - (dY * gazeCountdown / gazeFrames),
//      2, 2, LED_OFF);
//      if(gazeCountdown == 0) {    // Last frame?
//        eyeX = newX; 
//        eyeY = newY; // Yes.  What's new is old, then...
//        do { // Pick random positions until one is within the eye circle
//          newX = random(7); 
//          newY = random(7);
//          dX   = newX - 3;  
//          dY   = newY - 3;
//        } 
//        while((dX * dX + dY * dY) >= 10);      // Thank you Pythagoras
//        dX            = newX - eyeX;             // Horizontal distance to move
//        dY            = newY - eyeY;             // Vertical distance to move
//        gazeFrames    = random(3, 15);           // Duration of eye movement
//        gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
//      }
//    } 
//    else {
//      // Not in motion yet -- draw pupil at current static position
//      matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
//    }
//
//
//    // Refresh all of the matrices in one quick pass
//    matrix.writeDisplay();
//    
//     if(millis()-checkMillis > random(10000,30000))
//    {
//      neutralNoise();
//      checkMillis = millis();
//    }
//
//
//    tapMillis = millis();
//
//    while(millis()-tapMillis < 40)
//    {
//      checkTaps();
//    }  
//    songMillis = millis();
//  }
//
//  while(mood == 2) // happy mood
//  {
//    // Draw eyeball in current state of blinkyness (no pupil).
//    matrix.clear();
//    // When counting down to the next blink, show the eye in the fully-
//    // open state.  On the last few counts (during the blink), look up
//    // the corresponding bitmap index.
//    matrix.drawBitmap(0, 0,
//    happyBlinkImg[
//      (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
//    blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
//    0                                       // No, show bitmap 0
//    ], 8, 8, LED_ON);
//    // Decrement blink counter.  At end, set random time for next blink.
//    if(--blinkCountdown == 0) blinkCountdown = random(5, 180);
//
//    // Add a pupil (2x2 black square) atop the blinky eyeball bitmap.
//    // Periodically, the pupil moves to a new position...
//    if(--gazeCountdown <= gazeFrames) {
//      // Eyes are in motion - draw pupil at interim position
//      matrix.fillRect(
//      newX - (dX * gazeCountdown / gazeFrames),
//      newY - (dY * gazeCountdown / gazeFrames),
//      2, 2, LED_OFF);
//      if(gazeCountdown == 0) {    // Last frame?
//        eyeX = newX; 
//        eyeY = newY; // Yes.  What's new is old, then...
//        do { // Pick random positions until one is within the eye circle
//          newX = random(7); 
//          newY = random(4);
//          dX   = newX - 3;  
//          dY   = newY - 3;
//        } 
//        while((dX * dX + dY * dY) >= 10);      // Thank you Pythagoras
//        dX            = newX - eyeX;             // Horizontal distance to move
//        dY            = newY - eyeY;             // Vertical distance to move
//        gazeFrames    = random(3, 15);           // Duration of eye movement
//        gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
//      }
//    } 
//    else {
//      // Not in motion yet -- draw pupil at current static position
//      matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
//    }
//
//
//    // Refresh all of the matrices in one quick pass
//    matrix.writeDisplay();
//
//    if(millis()-checkMillis > random(10000,30000))
//    {
//      happyNoise();
//      checkMillis = millis();
//    }
//
//    tapMillis = millis();
//
//    while(millis()-tapMillis < 40)
//    {
//      checkTaps();
//    }  
//
//  }
//
//  while(mood==3) // annoyed mood
//  {
//    // Draw eyeball in current state of blinkyness (no pupil).
//    matrix.clear();
//    // When counting down to the next blink, show the eye in the fully-
//    // open state.  On the last few counts (during the blink), look up
//    // the corresponding bitmap index.
//    matrix.drawBitmap(0, 0,
//    annoyedBlinkImg[
//      (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
//    blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
//    0                                       // No, show bitmap 0
//    ], 8, 8, LED_ON);
//    // Decrement blink counter.  At end, set random time for next blink.
//    if(--blinkCountdown == 0) blinkCountdown = random(5, 180);
//
//    // Add a pupil (2x2 black square) atop the blinky eyeball bitmap.
//    // Periodically, the pupil moves to a new position...
//    if(--gazeCountdown <= gazeFrames) {
//      // Eyes are in motion - draw pupil at interim position
//      matrix.fillRect(
//      newX - (dX * gazeCountdown / gazeFrames),
//      newY - (dY * gazeCountdown / gazeFrames),
//      2, 2, LED_OFF);
//      if(gazeCountdown == 0) {    // Last frame?
//        eyeX = newX; 
//        eyeY = newY; // Yes.  What's new is old, then...
//        do { // Pick random positions until one is within the eye circle
//          newX = random(7); 
//          newY = random(3,7);
//          dX   = newX - 3;  
//          dY   = newY - 3;
//        } 
//        while((dX * dX + dY * dY) >= 10);      // Thank you Pythagoras
//        dX            = newX - eyeX;             // Horizontal distance to move
//        dY            = newY - eyeY;             // Vertical distance to move
//        gazeFrames    = random(3, 15);           // Duration of eye movement
//        gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
//      }
//    }
//    else {
//      // Not in motion yet -- draw pupil at current static position
//      matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
//    }
//
//    // Refresh all of the matrices in one quick pass
//    matrix.writeDisplay();
//    
//    if(millis()-checkMillis > random(10000,30000))
//    {
//      angryNoise();
//      checkMillis = millis();
//    }
//
//    tapMillis = millis();
//
//    while(millis()-tapMillis < 40)
//    {
//      checkTaps();
//    }    
//  }
