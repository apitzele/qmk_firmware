#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
      return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  }

  return rotation;
}


bool oled_task_user(void) {
  if (is_keyboard_master()) {

      // Host Keyboard LED Status
      led_t led_state = host_keyboard_led_state();
      oled_write_ln_P(led_state.num_lock ? PSTR("NUM\n") : PSTR("\n"),  false);
      oled_write_ln_P(led_state.caps_lock ? PSTR("CAP\n") : PSTR("\n"), false);
      oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR\n") : PSTR("\n"), false);

      oled_write_ln_P(PSTR("\n\n\n\n\n\n"), false);
      switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_ln_P(PSTR("MAIN"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("NAV"), false);
            break;
        case _SYML:
            oled_write_ln_P(PSTR("SYM L"), false);
            break;
        case _SYMR:
            oled_write_ln_P(PSTR("SYM R"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?"), false);
            break;
      }
  } else {
    // Display a message or logo on the slave side
    oled_write_P(PSTR("Not connected\n"), false);
  }

  return false;
}
#endif