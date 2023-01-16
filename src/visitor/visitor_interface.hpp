#ifndef VISITOR_INTERFACE_H
#define VISITOR_INTERFACE_H


class VisitorInterface {
  private:
  public:
  VisitorInterface();

  virtual auto visit() -> void = 0;

  virtual ~VisitorInterface();
};

#endif // VISITOR_INTERFACE_H
