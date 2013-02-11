/*
 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Deviation is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Deviation.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mixer_simple.h"
static struct timer_page * const tp = &pagemem.u.timer_page;
#define gui (&gui_objs.u.timer)

static void update_countdown(u8 idx);
const char *timer_str_cb(guiObject_t *obj, const void *data);
static const char *set_source_cb(guiObject_t *obj, int dir, void *data);
static void toggle_source_cb(guiObject_t *obj, void *data);
static void toggle_timertype_cb(guiObject_t *obj, void *data);
static const char *set_timertype_cb(guiObject_t *obj, int dir, void *data);
static const char *set_start_cb(guiObject_t *obj, int dir, void *data);

static const char *show_timerperm_cb(guiObject_t *obj, const void *data);
static void reset_timerperm_cb(guiObject_t *obj, const void *data);

static void _show_page();

void PAGE_TimerInit(int page)
{
    (void)page;
    PAGE_SetModal(0);
    PAGE_RemoveAllObjects();
    _show_page();
}

void PAGE_TimerEvent()
{
}
const char *timer_str_cb(guiObject_t *obj, const void *data)
{
    (void)obj;
    int i = (long)data;
    sprintf(tp->tmpstr, _tr("Timer%d:"), i + 1);
    return tp->tmpstr;
}

const char *set_source_cb(guiObject_t *obj, int dir, void *data)
{
    (void) obj;
    u8 idx = (long)data;
    struct Timer *timer = &Model.timer[idx];
    u8 is_neg = MIXER_SRC_IS_INV(timer->src);
    u8 changed;
    u8 max = NUM_SOURCES;
    u8 step = 1;
    if (Model.mixer_mode == MIXER_SIMPLE)  {
        max = mapped_simple_channels.throttle + NUM_INPUTS +1;
        step = max;
    }
    u8 src = GUI_TextSelectHelper(MIXER_SRC(timer->src), 0, max, dir, step, step, &changed);
    MIXER_SET_SRC_INV(src, is_neg);
    if (changed) {
        timer->src = src;
        TIMER_Reset(idx);
    }
    GUI_TextSelectEnablePress((guiTextSelect_t *)obj, MIXER_SRC(src));
    return INPUT_SourceName(tp->tmpstr, src);
}

void toggle_source_cb(guiObject_t *obj, void *data)
{
    u8 idx = (long)data;
    struct Timer *timer = &Model.timer[idx];
    if(MIXER_SRC(timer->src)) {
        MIXER_SET_SRC_INV(timer->src, ! MIXER_SRC_IS_INV(timer->src));
        TIMER_Reset(idx);
        GUI_Redraw(obj);
    }
}

const char *set_resetsrc_cb(guiObject_t *obj, int dir, void *data)
{
    (void) obj;
    u8 idx = (long)data;
    struct Timer *timer = &Model.timer[idx];
    u8 is_neg = MIXER_SRC_IS_INV(timer->resetsrc);
    u8 changed;
    u8 max = NUM_SOURCES;
    u8 step = 1;
    if (Model.mixer_mode == MIXER_SIMPLE && Model.type == MODELTYPE_HELI)  { //Improvement: only to intelligent switch setting for heli type in standard mode
        max = mapped_simple_channels.throttle + NUM_INPUTS +1;
        step = max;
    }
    u8 resetsrc = GUI_TextSelectHelper(MIXER_SRC(timer->resetsrc), 0, max, dir, step, step, &changed);
    MIXER_SET_SRC_INV(resetsrc, is_neg);
    if (changed) {
        timer->resetsrc = resetsrc;
        TIMER_Reset(idx);
    }
    GUI_TextSelectEnablePress((guiTextSelect_t *)obj, MIXER_SRC(resetsrc));
    return INPUT_SourceName(tp->tmpstr, resetsrc);
}

void toggle_resetsrc_cb(guiObject_t *obj, void *data)
{
    u8 idx = (long)data;
    struct Timer *timer = &Model.timer[idx];
    if(MIXER_SRC(timer->resetsrc)) {
        MIXER_SET_SRC_INV(timer->resetsrc, ! MIXER_SRC_IS_INV(timer->resetsrc));
        TIMER_Reset(idx);
        GUI_Redraw(obj);
    }
}

const char *set_timertype_cb(guiObject_t *obj, int dir, void *data)
{
    (void) obj;
    u8 idx = (long)data;
    u8 changed;
    struct Timer *timer = &Model.timer[idx];
    timer->type = GUI_TextSelectHelper(timer->type, 0, TIMER_LAST - 1, dir, 1, 1, &changed);
    if (changed){
        TIMER_Reset(idx);
    	update_countdown(idx);
    }
    switch (timer->type) {
    case TIMER_STOPWATCH: return _tr("stopwatch");
    case TIMER_COUNTDOWN: return _tr("countdown");
    case TIMER_PERMANENT: return _tr("permanent");
    case TIMER_LAST: break;
    }
    return "";
}

void toggle_timertype_cb(guiObject_t *obj, void *data)
{
    u8 idx = (long)data;
    struct Timer *timer = &Model.timer[idx];
    timer->type = TIMER_LAST == timer->type + 1 ? 0 : timer->type + 1;     
    TIMER_Reset(idx);
    update_countdown(idx);
    GUI_Redraw(obj);
}

const char *set_start_cb(guiObject_t *obj, int dir, void *data)
{
    (void)obj;
    u8 idx = (long)data;
    u8 changed;
    struct Timer *timer = &Model.timer[idx];
    timer->timer = GUI_TextSelectHelper(timer->timer, 0, TIMER_MAX_VAL, dir, 5, 30, &changed);
    if (changed)
        TIMER_Reset(idx);
    TIMER_SetString(tp->timer, timer->timer*1000);
    return tp->timer;
}

const char *show_timerperm_cb(guiObject_t *obj, const void *data)
{
  (void)obj;
  (void)data;
  TIMER_SetString(tp->tmpstr,(long)Model.permanent_timer);
  return tp->tmpstr;
}

void reset_timerperm_cb(guiObject_t *obj, const void *data)
{
  (void)obj;
  (void)data;
  PAGE_ShowResetPermTimerDialog(obj);
}
