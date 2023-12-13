#ifdef OLED_ENABLE

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_P(PSTR("DEFAULT\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("NUMBERS\n"), false);
            break;
         case _NAV:
            oled_write_P(PSTR("NAVIGATION\n"), false);
            break;
         case _SYML:
            oled_write_P(PSTR("SYMBOLS LEFT\n"), false);
            break;
         case _SYMR:
            oled_write_P(PSTR("SYMBOLS RIGHT\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
  } //   else {
//     render_logo();
//   }
  return false;
}
#endif