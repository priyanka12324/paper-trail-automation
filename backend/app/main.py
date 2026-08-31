from fastapi import FastAPI

app = FastAPI(
    title="Paper Trail Automation API",
    description="Backend API for AI-assisted workplace knowledge capture and approval.",
    version="0.1.0",
)


@app.get("/")
def root():
    return {
        "app": "Paper Trail Automation",
        "status": "online",
        "version": "0.1.0",
    }


@app.get("/health")
def health_check():
    return {"status": "healthy"}
