#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Editor {
public:
  Editor() {
    vec_.clear();
  }

  void Add(char ch) {
    vec_.push_back(ch);
    for each (char var in vec_) {
      cout << var;
    }
    cout << endl;
  }

  void Delete() {
    vec_.pop_back();
    for each (char var in vec_) {
      cout << var;
    }
    cout << endl;
  }

private:
  vector<char> vec_;
};

class Command {
public:
  Command(Editor* editor) {
    editor_ = editor;
  }
  virtual ~Command() {
    cout << "Destruct" << endl;
  }

  virtual void Execute() = 0;
  virtual void Undo() = 0;

protected:
  Editor* editor_;
};

class EditCommand : public Command {
public:
  // 将命令对象化，可进行保存。
  EditCommand(Editor* editor, char ch) : Command(editor) {
    ch_ = ch;
  }
  ~EditCommand() {
    cout << ch_ << endl;
  }
  virtual void Execute() {
    editor_->Add(ch_);
  }

  virtual void Undo() {
    editor_->Delete();
  }

private:
  char ch_;
};

class CommandManager {
public:
  CommandManager() {}
  ~CommandManager() {
    for each (Command* command in redo_commands) {
      delete command;
    }
    for (Command* command : undo_commands) {
      delete command;
    }
  }

  void Execute(Command* command) {
    redo_commands.clear();
    undo_commands.push_back(command);
    command->Execute();
  }

  void Redo() {
    if (redo_commands.empty()) {
      return;
    }
    Command* command = redo_commands.back();
    undo_commands.push_back(command);
    command->Execute();
    redo_commands.pop_back();
  }

  void Undo() {
    if (undo_commands.empty()) {
      return;
    }
    Command* command = undo_commands.back();
    redo_commands.push_back(command);
    command->Undo();
    undo_commands.pop_back();
  }

  bool CanRedo() {
    return !redo_commands.empty();
  }

  bool CanUndo() {
    return !undo_commands.empty();
  }

private:
  list<Command*> redo_commands;
  list<Command*> undo_commands;
};

class TextFile {
public:
  CommandManager& GetCommandManager(){
    return command_manager_;
  }
private:
  CommandManager command_manager_;
};


int main1() {
  Editor* editor = new Editor;
  Command* edit_command1 = new EditCommand(editor, '1');
  Command* edit_command2 = new EditCommand(editor, '2');
  Command* edit_command3 = new EditCommand(editor, '3');
  CommandManager* command_manager = new CommandManager;
  command_manager->Execute(edit_command1);
  command_manager->Execute(edit_command2);
  command_manager->Execute(edit_command3);
  command_manager->Undo();
  command_manager->Undo();
  command_manager->Redo();
  command_manager->Redo();
  command_manager->Undo();
  command_manager->Redo();

  delete editor;
  delete command_manager;



  return 0;
}

