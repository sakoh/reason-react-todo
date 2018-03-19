let str = ReasonReact.stringToElement;

type item = {
  id: int,
  title: string,
  completed: bool
};

let component = ReasonReact.statelessComponent("TodoItem");
let make = (~item, ~onToggle, ~deleteItem, _children) => {
  ...component,
  render: (_) =>
    <div className="item" onClick=((_evt) => onToggle())>
      <input
        _type="checkbox"
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      (str(item.title))
      <button onClick=((_evt) => deleteItem())>
        (str("Remove"))
      </button>  
    </div>
};
