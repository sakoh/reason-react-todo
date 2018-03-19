open TodoItem; 

type state = {
  items: list(item)
};

type action =
  | AddItem(string)
  | DeleteItem(int)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);
let newItem = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false}
};
let make = (_children) => {
  ...component,
  initialState: () => {
    items: [{
      id: 0,
      title: "Write some things to do",
      completed: false
    }]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
    | DeleteItem(id) => ReasonReact.Update({ items: List.filter(item => item.id != id, items) })
    | ToggleItem(id) => {
        let items =
          List.map(
            (item) =>
              item.id === id ?
                {...item, completed: ! item.completed} : item,
            items
          );
        ReasonReact.Update({items: items})
      }
    },
  render: ({
    state: { 
      items 
    }, 
    reduce, 
  }) => {
    let numItems = List.length(items);

    <div className="app">
      <div className="title">
        (str("What to do"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (
          ReasonReact.arrayToElement(Array.of_list(List.map(
            (item) =>
              <TodoItem
                key=(string_of_int(item.id))
                onToggle=(reduce(() => ToggleItem(item.id)))
                deleteItem=(reduce(() => DeleteItem(item.id)))
                item
              />,
            items
          )))
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
