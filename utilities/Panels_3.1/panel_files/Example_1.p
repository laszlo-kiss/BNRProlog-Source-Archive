/*
*
*  $Header: /disc9/sniff/repository/BNRProlog/utilities/Panels_3.1/panel_files/RCS/Example_1.p,v 1.1 1995/09/22 11:24:05 harrisja Exp $
*
*  $Log: Example_1.p,v $
 * Revision 1.1  1995/09/22  11:24:05  harrisja
 * Initial version.
 *
*
*/

/*
 *   Example 1
 *
 *   BNR Prolog
 *
 *   Copyright � Bell-Northern Research Ltd. 1991
 */

/****************************************************************************/

  /*  Basic panel maker example.
      --------------------------

� Try the buttons in the example panel.

  The event handlers for this example
  panel are in this file -- take a look
  at them.

� Try some basic editing:
    Slide the buttons around,
    resize the window, ...
  
� Close your editing by clicking on the
  close box of the panel.
 
  This file will be re_loaded and will 
  scroll down to the bottom.
  

--------------------------------------------------------------- 

             -- Panel event handlers --

--------------------------------------------------------------*/

panel_event('Example 1',open):-
    beep,beep.

panel_event('Example 1',select(_,_),button('Time',Etc..)):-
    timedate(Time,Date),
    panel_view('Example 1',field(show):=Time).
    
    % 'select' reacts as soon as the mouse is dowm

panel_event('Example 1',click,button('Date')):-
    timedate(Time,Date),
    panel_view('Example 1',show:=Date).  

    % 'click' is the mouseup after a select
    % the button object responds to the 'select' (and inverts).
    % 'show' is used as short-hand for field(show)

panel_event('Example 1',close):-
    beep,beep,
    context('Example_1',Path),
    concat(Window,'.a',Path)->true;Window=Path,
    closewindow(Window)->true,
    exit_context('Example_1').


/*--------------------------------------------------------------

   -- Panel layout definition generated by panel maker --

  Note that 'panel_window' and 'panel_content' are updated
  when you close the panel after having edited it.
  The updated file is then reloaded (as a context).

--------------------------------------------------------------*/

panel_definition('Example 1' , 
    pos(300,123) ,
    size(191, 156) ,
    options(nogrowdocproc) , 
    button('Date', [56, 100, 136, 120], _1) ,
    button('Time', [56, 68, 136, 88], _2) ,
    field(show, [44, 26, 144, 46], _3) ).

$initialization:- panel_open('Example 1').
