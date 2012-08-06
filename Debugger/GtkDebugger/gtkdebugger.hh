#ifndef __BATS_GTKDEBUGGER_HH__
#define __BATS_GtKDEBUGGER_HH__

#include "../debugger.hh"

#include <gtkmm.h>
#include <queue>

namespace bats
{
  extern "C" void onDrawingAreaExpose(GtkObject *object, gpointer user_data);

  class GtkDebugger : public Debugger
  {
    friend class Singleton<Debugger>;
    
    public:
      void init(int argc, char** argv);
      void start();
      void run();
      
      void reDraw();
      
      void debug(std::string const& dbg)
      {
        if (d_running)
        {
          d_dbgTextLock.lock();
          d_dbg += dbg;
          d_dbgTextLock.unlock();
        }
      }

      bool isEnabled() { return true; }
      bool isVerbose() { return false; }
      void setVerbose(bool isVerbose) { }
      
      void plot(std::string const& curve, float value);
      
      void draw(rf<Shape> shape) { d_shapes.push_back(shape); }
      void drawForPeriod(rf<Shape> shape, double durationSeconds) {}
      void drawUntil(rf<Shape> shape, double time) {}
      
      Glib::Dispatcher redraw_dispatch;
      Glib::Dispatcher dbg_text_dispatch;
      
    private:
      bool d_running;
      unsigned d_ticks;
      
      pthread_t d_thread;
      Gtk::Main* d_kit;
      
      Gtk::Window* d_window;
      Gtk::DrawingArea* d_drawingArea;
      Gtk::TextView* d_dbgText;
      Gtk::DrawingArea* d_curveDrawingArea;
      Gtk::TreeView* d_curvesList;
      Glib::RefPtr<Gtk::ListStore> d_curvesListStore;
      Glib::RefPtr<Gtk::TreeStore> d_behaviorTreeStore;
      
      Glib::Mutex d_dbgTextLock;
      std::string d_dbg;
      
      std::map<std::string, Curve> d_curves;
      
      std::vector<rf<Shape> > d_shapes;
      
      GtkDebugger ();

      void onRedraw() { d_drawingArea->queue_draw(); }
      void onThinkEnd();
      void onDbgText();

      void onBehaviorEvent(rf<BehaviorEvent> event) {}
      
      void drawField(Cairo::RefPtr<Cairo::Context> context);
      void drawSelf(Cairo::RefPtr<Cairo::Context> context);
      void drawBall(Cairo::RefPtr<Cairo::Context> context);
      void drawPlayers(Cairo::RefPtr<Cairo::Context> context);
      void drawShapes(Cairo::RefPtr<Cairo::Context> context);
      
      void drawCurve();
  };
  
};


#endif /* __BATS_GTKDEBUGGER_HH__ */

