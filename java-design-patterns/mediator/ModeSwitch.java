public class ModeSwitch {
  Mode mode = Mode.LIST;  

  ModeMediator modeMediator;

  public void setModeMediator (ModeMediator _modeMediator) {
    modeMediator = _modeMediator;
  }

  public void toggleMode () {
    mode = mode == Mode.LIST ? Mode.GALLERY : Mode.LIST;

    if (modeMediator != null) {
      modeMediator.onModeChange(mode);
    }
  }
}

enum Mode { LIST, GALLERY }