import java.util.ArrayList;

public class ModeMediator {
  ArrayList<ModeListener> listeners = new ArrayList<>();

  public void addListener(ModeListener listener) {
    listeners.add(listener);
  }
  public void onModeChange (Mode mode) {
    for (ModeListener listener : listeners) {
      listener.onModeChange(mode);
    }
  }
}