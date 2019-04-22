/*
 * Selectors.re
 *
 * Helpers to map the State.t to more usable values
 */

open Oni_Core;

let getActiveEditor = (state: State.t) => {
  EditorGroup.getActiveEditor(state.editors);
};

let getBufferById = (state: State.t, id: int) => {
  Buffers.getBuffer(id, state.buffers);
};

let getBufferForEditor = (state: State.t, editor: Editor.t) => {
  Buffers.getBuffer(editor.bufferId, state.buffers);
};

let getActiveBuffer = (state: State.t) => {
  let editorOpt = state |> getActiveEditor; 
  
  switch (editorOpt) {
  | Some(editor) => getBufferForEditor(state, editor)
  | None => None
  };
};

let getTabs = (state: State.t, editorGroup: EditorGroup.t) => {
    let f = (editorId: int) => {
        let editor = EditorGroup.getEditorById(editorId, editorGroup)
        let buffer = getBufferById(state, editor.bufferId);

        switch (buffer) {
        | Some(v) => Tab.ofBuffer(~buffer=v, ~active=false, ())
        | None => Tab.create(~id=-1, ~title="Unknown", ())
        }
    };

    editorGroup.reverseTabOrder
    |> List.rev
    |> List.map(f)
}